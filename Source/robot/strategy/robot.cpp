/**
	\class Robot
	\brief Parent class for Kicker and Keeper
	\author Gert Mertes
*/

#include "robot.h"
#include <iostream>

// ---------------------------------------------------------------------------
Robot::Robot()
{
        lastInstruction = 'a';
	co = 0;
}

// ---------------------------------------------------------------------------
Robot::~Robot()
{
	//unused
}

void Robot::setCoords(VisionData *coords)
{
	std::cout << "robot scoords" << std::endl;	
	this->co = coords;
}

void Robot::setll(LowLevel *lowl)
{
	this->ll = lowl;

}

void Robot::run()
{

}
