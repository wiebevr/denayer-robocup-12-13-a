/*
 * Kicker.cpp
 *
 *  Created on: 21-feb.-2013
 *      Author: Pascal Muys
 */

#include "kicker.h"
#include <stdio.h>
#include <math.h>

Kicker::Kicker()
{
	// TODO Auto-generated constructor stub
	kick_distance = 50;
	max_speed = 100;
}

Kicker::~Kicker()
{
	// TODO Auto-generated destructor stub
}

void Kicker::run()
{
	calcKickPos();

	if( rob_posx == kick_posx && rob_posy == kick_posy ) //Robot at kicking position
	{
		if( turnTo(ball_posx, ball_posy) == 0 )	 //Robot turned towards ball
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
	int x_t = x - rob_posx;
	int y_t = y - rob_posy;

	if(x == 0) {
		// Turn till rotation = 90
	}

	//int beta = atan2(x_t, y_t); // veeeery slooow atan
	int f = rob_roty/rob_rotx	// let image processing do the hard work
	
	int y_d = x*f;

	if(y_d != y_t)
	{
		
		ll::turnLeft(max_speed);
		return 1;	// turning...
	}
	else
	{
		return 0;	// turned towards point!
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
