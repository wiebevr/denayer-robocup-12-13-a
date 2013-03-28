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
	
	mode = 1;
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
	keeper->setCoords(coords);
	kicker->setCoords(coords);	
}

// ---------------------------------------------------------------------------
