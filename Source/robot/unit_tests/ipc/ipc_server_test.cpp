#include "ipc/ipc_server.h"

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    IPCServer server(IPCSocket::STRATEGY_LOW_LEVEL);
    std::string message;
    char buffer[64];
    server.open();
    std::cerr << "Connection established" << std::endl;

#if 1
    while (true)
    {
        server >> message;
        std::cerr << message << std::endl;
        server << message;
    }
#endif
    return 0;
}
