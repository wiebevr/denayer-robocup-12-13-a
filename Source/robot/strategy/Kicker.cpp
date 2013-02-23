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
	//word in een lus opgeroepen om alles te doen
	calcKickPos();
}

void Kicker::calcKickPos()
{
	//TODO find proper functions to get coordinates
	int x = Coords.getGoalX() - Coords.getBallX();
	int y = Coords.getGoalY() - Coords.getBallY();

	int ball_goal_distance = pythagoras(x, y);
	int factor = kick_distance/ball_goal_distance;

	kick_posX = Coords.getBallX() - (factor*x);
	kick_posY = Coords.getBallY() - (factor*y);
}

int Kicker::pythagoras(int x, int y)
{
	double z;
	z = sqrt( (x*x)+(y*y) );
	return z;
}
