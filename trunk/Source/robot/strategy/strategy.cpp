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
	keeper = new Keeper(&co, &ll);
	kicker = new Kicker(&co, &ll);
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
	while(1)
	{
		co = getCoords();
		
		if(1/*ll.iets == true*/)
		{
			keeper->run();
		}
		else
		{
			kicker->run();
		}
	}
}

// ---------------------------------------------------------------------------
void Strategy::setGame(const Game & game)
{
    this->co = game;
}

#if 0
// ---------------------------------------------------------------------------
VisionData Strategy::getCoords()
{
/*
	IPCClient low_level(IPCSocket::WIFI_STRATEGY);
    IPCServer wifi(IPCSocket::WIFI_STRATEGY);
    low_level.open();
    wifi.open();
    
    char buffer[IPCSocket::MAX_MESSAGE_LEN];
    int length;

    while (true)
    {
        // Send the data coming from wifi directly to low_level.
        length = wifi.read(buffer, IPCSocket::MAX_MESSAGE_LEN);
        std::cout << "Recieved: '" << buffer << "'" << std::endl;
        std::cout << "Length: '" << length << "'" << std::endl;
        low_level.write(buffer, length);
    }

    return 0;
*/
}
