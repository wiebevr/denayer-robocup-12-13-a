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

Robot::setGame(const Game & game)
{
	this->game = game;
}

Robot::setll(LowLevel *ll)
{
	this->ll = ll;

}
