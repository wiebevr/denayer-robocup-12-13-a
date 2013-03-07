/**
	\class Robot
	\brief Parent class for Kicker and Keeper
	\author Gert Mertes
*/

#include "robot.h"

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
	this->co = coords;
}

void Robot::setll(LowLevel *ll)
{
	this->ll = ll;

}
