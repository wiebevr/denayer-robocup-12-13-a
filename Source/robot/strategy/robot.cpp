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
}

// ---------------------------------------------------------------------------
Robot::~Robot()
{
	//unused
}

Robot::setCoords(const VisionData & coords)
{
	this->coords = coords;
}

Robot::setll(LowLevel *ll)
{
	this->ll = ll;

}
