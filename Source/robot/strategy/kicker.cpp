/*
 * Kicker.cpp
 *
 *  Created on: 21-feb.-2013
 *      Author: Pascal Muys
 */

#include "kicker.h"
#include <iostream>

using namespace std;

Kicker::Kicker()
{
	// TODO Auto-generated constructor stub
	kick_distance = 4;
	max_speed = 100;
}

Kicker::~Kicker()
{
	// TODO Auto-generated destructor stub
}

void Kicker::run()
{
	calcKickPos();
	cout << "calc kickpos " << endl;
	cout << kick_posx << endl;
	cout << kick_posy << endl;
	if( co->robot1x == kick_posx && co->robot1y == kick_posy ) //Robot at kicking position
	{
		cout << "robot at kickpos " << endl;
		if( turnTo(co->ballx, co->bally) == 1 )	 //Robot turned towards ball
		{
			driveTo(co->ballx, co->bally);	 //Let's kick!
		}
		else
		{
			return;			 //Not completely turned yet
		}
	}
	else if( turnTo(kick_posx, kick_posy) == 1 )	 //Turned to kicking position?
	{
		cout << "turned to kickpos " << endl;
		driveTo(kick_posx, kick_posy);		 //Drive towards position
	}	
}

void Kicker::calcKickPos()
{
	float x = co->goal1x - co->ballx;
	float y = co->goal1y - co->bally;
	if(x != 0.00)
	{
		float f = y/x;	
		kick_posx = co->ballx - kick_distance;
		kick_posy = co->bally - f*kick_distance;
	}
	else
	{
		kick_posx = co->ballx;
		kick_posy = co->bally - kick_distance;
	}
}

float Kicker::pythagoras(float x, float y)
{
	float z;
	z = sqrt( (x*x)+(y*y) );
	return z;
}

int Kicker::turnTo(float x, float y)
{
	float x_t = x - co->robot1x;		//make triangle of robotcoords and pointcoords
	float y_t = y - co->robot1y;		//these are hor. and vert. sides

	if(x_t == 0.00)				// point is above us!
	{		
		cout << "x == 0 " << endl;
		if(co->robot1rotx == 0)
		{
			return 1;		//turned upwards
		}
		else if(co->robot1rotx < 0)
		{
			ll->turnRight(max_speed);
			return 0;
		}
		else
		{
			ll->turnLeft(max_speed);
			return 0;
		}
	}
	else					// slightly more complex turning
	{	
		int q_p = checkQuadrant(x_t,y_t);
		int q_r = checkQuadrant(co->robot1rotx, co->robot1roty);
		// if robot is looking in same quadrant as point
		if( q_p == q_r )
		{
			double f = co->robot1roty/co->robot1rotx;		// vector of the robots rotation
									// recalculate to smaller triangle
			int y_s = x_t*f;				// y/x = y'/x'= f => y = f*x

			if( abs(y_s) > abs(y_t) )			// if small triangle does not equal point-triangle
			{
				ll->turnRight(max_speed);		// turning...
				return 0;
			}
			else if( abs(y_s) < abs(y_t) )
			{
				ll->turnLeft(max_speed);
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
				ll->turnRight(max_speed);		// turn towards point-quadrant
				return 0;
			}
			else
			{
				ll->turnLeft(max_speed);
				return 0;
			}
		}
		else if( abs(q_r) == abs(q_p) )				// different sign, equal value
		{							// in opposing quadrants
			if( abs(x_t) > abs(y_t) )
			{
				ll->turnRight(max_speed);		// turn towards closest other quadrant
				return 0;
			}
			else
			{
				ll->turnLeft(max_speed);
				return 0;
			}
		}
		else							// both in left or right half
		{
			if( abs(q_r) > abs(q_p) )			// same as in upper-lower, but turn other way
			{
				ll->turnLeft(max_speed);		// turning...
				return 0;
			}
			else
			{
				ll->turnRight(max_speed);
				return 0;
			}
		}
	}
}

int Kicker::driveTo(float x, float y)
{
	if(co->robot1x == x && co->robot1y == y)
	{
		ll->driveForward(0);
		return 0;
	}
	else
	{
		ll->driveForward(max_speed);
		return 0;
	}
}

int Kicker::checkQuadrant( float x_coordinate, float y_coordinate)
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

