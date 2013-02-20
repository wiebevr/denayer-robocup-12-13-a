#include "ipc_client.h"

// Standard c
#include <cstring>

// Standard C++
#include <iostream>

// Socket programming
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

// ---------------------------------------------------------------------------
IPCClient::IPCClient(Name name)
    : IPCSocket(name)
{

}

// ---------------------------------------------------------------------------
IPCClient::~IPCClient()
{
}

// ---------------------------------------------------------------------------
bool IPCClient::open()
{
    // Create the socket.
    this->socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un socket_adress;
    socket_adress.sun_family = AF_UNIX;

    // Choose the adress (path).
    switch (this->name)
    {
        case IPCSocket::STRATEGY_LOW_LEVEL:
        strcpy(socket_adress.sun_path,
                IPCSocket::STRATEGY_LOW_LEVEL_PATH);
        break;
        case IPCSocket::WIFI_STRATEGY:
        strcpy(socket_adress.sun_path,
                IPCSocket::WIFI_STRATEGY_PATH);
        break;
    }

    // Connect to the server
    if (connect(this->socket_fd, (struct sockaddr *)&socket_adress, sizeof(struct sockaddr_un)) == -1)
    {
        std::cerr << "Connection failed." << std::endl;
        return false;
    }

    return true;
}
