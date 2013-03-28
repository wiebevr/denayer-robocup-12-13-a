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
	kick_distance = 0.1;
	maxSpeed = 100;
	walk_speed = 50;
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
		if( turnTo(co->ballx, co->bally) )	 //Robot turned towards ball
		{
			driveTo(co->ballx, co->bally, maxSpeed);	 //Let's kick!
		}
		else
		{
			return;			 //Not completely turned yet
		}
	}
	else if( turnTo(kick_posx, kick_posy) )	 //Turned to kicking position?
	{
		cout << "turned to kickpos " << endl;
		driveTo(kick_posx, kick_posy, walk_speed);		 //Drive towards position
	}	
}

void Kicker::calcKickPos()
{
	float goalx = (co->goal1x + co->goal2x)/2;
	float goaly = (co->goal1y + co->goal2y)/2;
	float x = goalx - co->ballx;
	float y = goaly - co->bally;
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
/*
Unnecessary
float Kicker::pythagoras(float x, float y)
{
	float z;
	z = sqrt( (x*x)+(y*y) );
	return z;
}
*/

/*
Replaced by Robot version
int Kicker::turnTo(float x, float y)
{
	float x_t = x - co->robot1x;		//make triangle of robotcoords and pointcoords
	float y_t = y - co->robot1y;		//these are hor. and vert. sides

	if(x == 0.00)				// point is above us! (or below)
	{		
		cout << "xt == 0 " << endl;
		if(co->robot1rotx == 0.00 )	//we're looking up! (or down)
		{
			if( (co->robot1roty == 1.00 && y>0) || (co->robot1roty == -1.00 && y<0) )
			{
				return 1;	//turned in same direction as point
			}
			else			//turned opposite direction, turn any way to change rotx
			{
				ll->turnRight(maxSpeed);
				return 0;
			}
		}
		else if( (co->robot1rotx < 0) )	//robot looks to left side
		{
			ll->turnRight(maxSpeed);
			return 0;
		}
		else				//robot looks to right side
		{
			ll->turnLeft(maxSpeed);
			return 0;
		}
	}
	else					// slightly more complex turning
	{	
		cout << "rotx not 0 " << endl;
		int q_p = checkQuadrant(x_t,y_t);
		int q_r = checkQuadrant(co->robot1rotx, co->robot1roty);
		cout << q_p << " " << q_r  << endl;
		// if robot is looking in same quadrant as point
		if( q_p == q_r )
		{
			cout << "qp = qr " << endl;
			double f = co->robot1roty/co->robot1rotx;		// vector of the robots rotation
									// recalculate to smaller triangle
			int y_s = x_t*f;				// y/x = y'/x'= f => y = f*x
			cout << fabs(y_s) << " " << fabs(y_t) << endl;			
			
			if( fabs(y_s) > fabs(y_t) )			// if small triangle does not equal point-triangle
			{
				ll->turnRight(maxSpeed);		// turning...
				return 0;
			}
			else if( fabs(y_s) < fabs(y_t) )
			{
				ll->turnLeft(maxSpeed);
				return 0;
			}
			else						// y_s == y_t
			{
				return 1;				// turned towards point!
			}
		}
		else if( (q_p < 0 && q_r < 0) || (q_p > 0 && q_r > 0) ) // both in upper or lower half
		{
			cout << "both upper or lower " << endl;
			if( fabs(q_r) > fabs(q_p) )
			{
				ll->turnRight(maxSpeed);		// turn towards point-quadrant
				return 0;
			}
			else
			{
				ll->turnLeft(maxSpeed);
				return 0;
			}
		}
		else if( fabs(q_r) == fabs(q_p) )				// different sign, equal value
		{							// in opposing quadrants
			cout << "diff sign, eq value " << endl;			
			if( fabs(x_t) > fabs(y_t) )
			{
				ll->turnRight(maxSpeed);		// turn towards closest other quadrant
				return 0;
			}
			else
			{
				ll->turnLeft(maxSpeed);
				return 0;
			}
		}
		else							// both in left or right half
		{
			cout << "else; other situation " << endl;
			if( fabs(q_r) > fabs(q_p) )			// same as in upper-lower, but turn other way
			{
				ll->turnLeft(maxSpeed);		// turning...
				return 0;
			}
			else
			{
				ll->turnRight(maxSpeed);
				return 0;
			}
		}
	}
}
*/

int Kicker::driveTo(float x, float y, int speed)
{
	if(co->robot1x >= x && co->robot1y >= y)
	{
		ll->driveForward(0);
		return 0;
	}
	else
	{
		cout << "heey " << endl;
		ll->driveForward(speed);
		return 0;
	}
}

/*
Replaced by Robot Turnto()
int Kicker::checkQuadrant( float x_coordinate, float y_coordinate)
{
	// check for point on origin  or axis
	if (x_coordinate == 0 || y_coordinate == 0)
	{	
		return 0;
	}
    	// check for quadrant I
    	else if(x_coordinate > 0 && y_coordinate > 0)
	{
        	return -1;
    	}
    	// check for quadrant II
    	else if(x_coordinate < 0 && y_coordinate > 0)
	{
        	return -2;
    	}
    	// check for quadrant III
    	else if(x_coordinate < 0 && y_coordinate < 0)
	{
    		return 2;
    	}
    	// check for quadrant IV
    	else
	{
        	return 1;
    	}
    	return 0;
} 
*/
