/*
 * Kicker.cpp
 *
 *  Created on: 21-feb.-2013
 *      Author: Pascal Muys
 */

#include "Kicker.h"
#include <stdio.h>
#include <math.h>

Kicker::Kicker()
{
	// TODO Auto-generated constructor stub
	kick_distance = 50;
}

Kicker::~Kicker()
{
	// TODO Auto-generated destructor stub
}

void Kicker::run()
{
	calcKickPos();

	int rob_posx = Coords::getRobotX();
	int rob_posy = Coords::getRobotY();
	int ball_posx = Coords::getBallX();
	int ball_posy = Coords::getBallY();

	if( rob_posx == kick_posx && rob_posy == kick_posy ) //Robot at kicking position
	{
		if( turnTo(ball_posx, ball_posy) == 1 )	 //Robot turned towards ball
		{
			driveTo(ball_posx, ball_posy);	 //Let's kick!
		}
		else
		{
			return 0;			 //Not completely turned yet
		}
	}
	else if( turnTo(kick_posx, kick_posy) == 1)	 //Turned to kicking position?
	{
		driveTo(kick_posx, kick_posy);		 //Drive towards position
	}	
}

void Kicker::calcKickPos()
{
	//TODO find proper functions to get coordinates
	int x = Coords::getGoalX() - Coords::getBallX();
	int y = Coords::getGoalY() - Coords::getBallY();

	int ball_goal_distance = pythagoras(x, y);
	int factor = kick_distance/ball_goal_distance;

	kick_posx = Coords.getBallX() - (factor*x);
	kick_posy = Coords.getBallY() - (factor*y);
}

int Kicker::pythagoras(int x, int y)
{
	double z;
	z = sqrt( (x*x)+(y*y) );
	return z;
}

int Kicker::turnTo(int x, int y)
{
	//TODO again find proper functions
	int x_t = x - Coords::getRobotX();
	int y_t = x - Coords::getRobotY();

	int alpha = Coords::getRobotAngle();
	int beta = atan2(x_t, y_t);

	LowLevel::Turn(alpha-beta);

	if(alpha-beta == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Kicker::driveTo(int x, int y)
{
	if(Coords::getRobotX() == x && Coords::getRobotY() == y)
	{
		LowLevel::Drive(0);
		return 1;
	}
	else
	{
		LowLevel::Drive(max_speed);
		return 0;
	}
}
