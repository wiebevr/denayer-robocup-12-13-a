/*
 * Kicker.cpp
 *
 *  Created on: 21-feb.-2013
 *      Author: Pascal Muys
 */

#include "kicker.h"
#include <stdio.h>
#include <stdlib.h>
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

	if( co::robot1x == kick_posx && co::robot1y == kick_posy ) //Robot at kicking position
	{
		if( turnTo(co::ballx, co::bally) == 0 )	 //Robot turned towards ball
		{
			driveTo(co::ballx, co::bally);	 //Let's kick!
		}
		else
		{
			return;			 //Not completely turned yet
		}
	}
	else if( turnTo(kick_posx, kick_posy) == 1)	 //Turned to kicking position?
	{
		driveTo(kick_posx, kick_posy);		 //Drive towards position
	}	
}

void Kicker::calcKickPos()
{
	//TODO get rid of pythagoras
	int x = co::goal1x - ballx;
	int y = goal1y - bally;

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
	int x_t = x - co::robot1x;		//make triangle of robotcoords and pointcoords
	int y_t = y - co::robot1y;		//these are hor. and vert. sides

	if(x_t == 0)				// point is above us!
	{					
	}
	else					// slightly more complex turning
	{	
		int q_p = checkQuadrant(x_t,y_t);
		int q_r = checkQuadrant(co::robot1rotx, co::robot1roty);
		// if robot is looking in same quadrant as point
		if( q_p == q_r )
		{
			double f = co::robot1roty/co::robot1rotx;	// vector of the robots rotation
									// recalculate to smaller triangle
			int y_s = x_t*f;				// y/x = y'/x'= f => y = f*x

			if( abs(y_s) > abs(y_t) )			// if small triangle does not equal point-triangle
			{
				ll::turnRight(max_speed);		// turning...
				return 0;
			}
			else if( abs(y_s) < abs(y_t) )
			{
				ll::turnLeft(max_speed);
				return 0;
			}
			else						// y_s == y_t
			{
				return 1;				// turned towards point!
			}
		}
		else if( (q_p < 0 && q_r < 0) || (q_p > 0 && q_r > 0) ) // both in upper or lower half
		{
			if( abs(q_r) > abs(q_p) )
			{
				ll::turnRight(max_speed);		// turn towards point-quadrant
				return 0;
			}
			else
			{
				ll::turnLeft(max_speed);
				return 0;
			}
		}
		else if( abs(q_r) == abs(q_p) )				// different sign, equal value
		{							// in opposing quadrants
			if( abs(x_t) > abs(y_t) )
			{
				ll::turnRight(max_speed);		// turn towards closest other quadrant
				return 0;
			}
			else
			{
				ll::turnLeft(max_speed);
				return 0;
			}
		}
		else							// both in left or right half
		{
			if( abs(q_r) > abs(q_p) )			// same as in upper-lower, but turn other way
			{
				ll::turnLeft(max_speed);		// turning...
				return 0;
			}
			else
			{
				ll::turnRight(max_speed);
				return 0;
			}
		}
	}
}

int Kicker::driveTo(int x, int y)
{
	if(co::robot1x == x && co::robot1y == y)
	{
		LowLevel::Drive(0);
		return 0;
	}
	else
	{
		LowLevel::Drive(max_speed);
		return 0;
	}
}

int Kicker::checkQuadrant(int x, int y)
{
	/* check for point on origin  or axis */
	if (x_coordinate == 0 || y_coordinate == 0)
	{	
		return 0;
	}
    	/* check for quadrant I */
    	else if(x_coordinate > 0 && y_coordinate > 0)
	{
        	return -1;
    	}
    	/* check for quadrant II */
    	else if(x_coordinate < 0 && y_coordinate > 0)
	{
        	return -2;
    	}
    	/* check for quadrant III */
    	else if(x_coordinate < 0 && y_coordinate < 0)
	{
    		return 2;
    	}
    	/* check for quadrant IV */
    	else
	{
        	return 1;
    	}
    	/* all possibilities covered by now */
    	/* terminate successfully */
    	return 0;
} 

