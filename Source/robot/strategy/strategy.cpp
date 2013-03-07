/**
	\class Strategy
	\brief Top level Strategy class
	\author Gert Mertes
*/

#include "strategy.h"
/*
#include "ipc/ipc_client.h"
#include "ipc/ipc_server.h"
*/

// ---------------------------------------------------------------------------
Strategy::Strategy()
{
	keeper = new Keeper();
	keeper.setll(&ll);
	kicker = new Kicker();
	kicker.setll(&ll);
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
		if(1/*ll.iets == true*/)
		{
			keeper->run();
		}
		else
		{
			kicker->run();
		}
}

// ---------------------------------------------------------------------------
void Strategy::setCoords(const VisionData & coords)
{
//    this->co = game;
	keeper.setCoords(coords);
	kicker.setCoords(coords);	
}

#if 0
// ---------------------------------------------------------------------------
