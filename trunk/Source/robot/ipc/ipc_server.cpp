// Includes
#include "ipc_server.h"

// Standard c
#include <cstring>

// Standard C++
#include <iostream>

// POSIX
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>

// ---------------------------------------------------------------------------
IPCServer::IPCServer(Name name)
    : IPCSocket(name)
{

}

// ---------------------------------------------------------------------------
IPCServer::~IPCServer()
{
}

// ---------------------------------------------------------------------------
bool IPCServer::open()
{

    int listen_fd;
    // Create the socket.
    listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
    }

    struct sockaddr_un socket_adress;
    socket_adress.sun_family = AF_UNIX;

    // Choose the adress (path).
    switch (this->name)
    {
    case IPCSocket::STRATEGY_LOW_LEVEL:
        unlink(IPCSocket::STRATEGY_LOW_LEVEL_PATH);
        strcpy(socket_adress.sun_path, IPCSocket::STRATEGY_LOW_LEVEL_PATH);
        break;
    case IPCSocket::WIFI_STRATEGY:
        unlink(IPCSocket::WIFI_STRATEGY_PATH);
        strcpy(socket_adress.sun_path, IPCSocket::WIFI_STRATEGY_PATH);
        break;
    }

    // Bind the socket.
    if (bind(listen_fd, (const sockaddr *)&socket_adress, sizeof(struct sockaddr_un)))
    {
        std::cerr << "Failed to bind socket." << std::endl;
        return false;
    }

    if (listen(listen_fd, 1) == -1)
    {
        std::cerr << "Failed to listen." << std::endl;
        return false;
    }

    this->socket_fd = accept(listen_fd, NULL, NULL);
    if (this->socket_fd == -1)
    {
        std::cerr << "accept() failed." << std::endl;
        return false;
    }

    return true;
}
