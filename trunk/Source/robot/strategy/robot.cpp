/**
	\class Robot
	\brief Parent class for Kicker and Keeper
	\author Gert Mertes
*/

#include "robot.h"

// ---------------------------------------------------------------------------
Robot::Robot(VisionData *co, LowLevel *ll)
{
/*
	Initialize pointer locations
*/
        this.co = co;
		this.ll = ll;
        lastInstruction = '';
}

// ---------------------------------------------------------------------------
Robot::~Robot()
{
	//unused
}