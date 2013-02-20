#include "ipc/ipc_client.h"

#include <iostream>

int main(int argc, char **argv)
{
    IPCClient client(IPCSocket::STRATEGY_LOW_LEVEL);
    char buffer[64];
    std::string message;
    client.open();
    std::cerr << "Connection established" << std::endl;

#if 1
    while (true)
    {
        std::cin.getline(buffer, 64);
        client << buffer; 
        std::cout << client << std::endl;
    }
#endif

    return 0;
}
