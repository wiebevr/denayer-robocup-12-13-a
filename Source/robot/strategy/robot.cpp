/**
	\class Robot
	\brief Parent class for Kicker and Keeper
	\author Gert Mertes
*/

#include "robot.h"

// ---------------------------------------------------------------------------
Robot::Robot(VisionData *c, LowLevel *l)
{
/*
	Initialize pointer locations
*/
	co = c;
	ll = l;
        lastInstruction = 'a';
}

// ---------------------------------------------------------------------------
Robot::~Robot()
{
	//unused
}
