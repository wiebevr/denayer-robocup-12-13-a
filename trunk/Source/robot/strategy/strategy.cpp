/**
	\class Strategy
	\brief Top level Strategy class
	\author Gert Mertes
*/

#include "strategy.h"
#include <iostream>
/*
#include "ipc/ipc_client.h"
#include "ipc/ipc_server.h"
*/

// ---------------------------------------------------------------------------
Strategy::Strategy()
{
	keeper = new Keeper();
	keeper->setll(&ll);
	kicker = new Kicker();
	kicker->setll(&ll);
	
	mode = 0;
}

// ---------------------------------------------------------------------------
Strategy::~Strategy()
{
	delete keeper;
	delete kicker;
}

// ---------------------------------------------------------------------------
void Strategy::run()
{
		std::cout << "strat run" << std::endl;
		if(mode)
		{
			keeper->run();
		}
		else
		{
			kicker->run();
		}
}

// ---------------------------------------------------------------------------
void Strategy::setCoords(VisionData *coords)
{
//    this->co = game;
	coords->robot1x = round((coords->robot1x * 100));
	coords->robot1y = round((coords->robot1y * 100));
	coords->robot1rotx = round((coords->robot1rotx * 100));
	coords->robot1roty = round((coords->robot1roty * 100));
	coords->robot2x = round((coords->robot2x * 100));
	coords->robot2y = round((coords->robot2y * 100));
	coords->robot2rotx = round((coords->robot2rotx * 100));
	coords->robot2roty = round((coords->robot2roty * 100));
	
	coords->ballx = round((coords->ballx * 100));
	coords->bally = round((coords->bally * 100));

	coords->goal1x = round((coords->goal1x * 100));
	coords->goal1y = round((coords->goal1y * 100));
	coords->goal2x = round((coords->goal2x * 100));
	coords->goal2y = round((coords->goal2y * 100));

	keeper->setCoords(coords);
	kicker->setCoords(coords);	
}

// ---------------------------------------------------------------------------

void Strategy::setMode(int m)
{
	mode = m;
}
