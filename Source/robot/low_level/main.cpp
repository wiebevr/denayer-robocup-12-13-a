// Includes:
#include "ipc/ipc_server.h"

// Standard:
#include <iostream>

// ---------------------------------------------------------------------------
int main(int argc, char **argv)
{
    IPCServer strategy(IPCSocket::WIFI_STRATEGY);
    strategy.open();
    
    char buffer[IPCSocket::MAX_MESSAGE_LEN];
    int length;

    while (true)
    {
        // Send the data coming from wifi directly to low_level.
        std::cout << strategy << std::endl;
    }

    return 0;
}
