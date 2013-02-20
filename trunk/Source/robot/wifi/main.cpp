// Includes:
#include "ipc/ipc_client.h"

// Standard:
#include <iostream>

// ---------------------------------------------------------------------------
int main(int argc, char **argv)
{
    IPCClient ipc(IPCSocket::WIFI_STRATEGY);
    char buffer[IPCSocket::MAX_MESSAGE_LEN];
    ipc.open();

    while (true)
    {
        std::cin.getline(buffer, IPCSocket::MAX_MESSAGE_LEN);
        ipc << buffer;
    }

    return 0;
}
