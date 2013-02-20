// Includes:
#include "ipc/ipc_client.h"
#include "ipc/ipc_server.h"

// Standard:
#include <iostream>

// ---------------------------------------------------------------------------
int main(int argc, char **argv)
{
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
}
