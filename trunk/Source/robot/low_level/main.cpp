// Includes:
#include "ipc/ipc_server.h"

#include "low_level.h"

// Standard:
#include <iostream>

// ---------------------------------------------------------------------------
int main(int argc, char **argv)
{
    IPCServer strategy(IPCSocket::WIFI_STRATEGY);
    strategy.open();
    
    char buffer[IPCSocket::MAX_MESSAGE_LEN];
    int length;
    LowLevel * ll = new LowLevel();
    ll->driveForward(100);
    for( int i = 0; i < 100000; i++) {}
    ll->stopMoving();
    while (true)
    {
        std::cout << strategy << std::endl;
    }

    return 0;
}
