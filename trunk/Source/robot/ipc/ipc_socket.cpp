#include "ipc_socket.h"

// Standard lib:
#include <string>
#include <cstring>
#include <cstdlib>

// POSIX:
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

const char *IPCSocket::WIFI_STRATEGY_PATH = "/tmp/wifi_strat.socket";
const char *IPCSocket::STRATEGY_LOW_LEVEL_PATH = "/tmp/strat_ll.socket";

// ---------------------------------------------------------------------------
IPCSocket::IPCSocket(Name name)
{
    this->name = name;
    this->socket_fd = 0;
}

// ---------------------------------------------------------------------------
IPCSocket::~IPCSocket()
{
    cleanUp();
}

// ---------------------------------------------------------------------------
const IPCSocket &IPCSocket::operator<<(const std::string &message)
{
    this->write(message.c_str(), message.size() + 1);
    return *this;
}

// ---------------------------------------------------------------------------
const IPCSocket &IPCSocket::operator>>(std::string &message)
{
    char buffer[MAX_MESSAGE_LEN];
    this->read(buffer, MAX_MESSAGE_LEN);
    message = std::string(buffer);

    return *this;
}

// ---------------------------------------------------------------------------
void IPCSocket::write(const char *data, int size)
{
    int res = send(this->socket_fd, data, size, 0);
    if(res < 0)
    {
        cleanUp();
        exit(1);
    }
}

// ---------------------------------------------------------------------------
int IPCSocket::read(char *data, int size)
{
    char buffer[MAX_MESSAGE_LEN];
    int res = recv(this->socket_fd, data, size, 0);
    if (res < 1)
    {
        cleanUp();
        exit(1);
    }
    return res;
}

// ---------------------------------------------------------------------------
void IPCSocket::cleanUp()
{
    if (this->socket_fd)
    {
        close(this->socket_fd);
        this->socket_fd = 0;
    }
}

// ---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream &out, IPCSocket &socket)
{
    char buffer[IPCSocket::MAX_MESSAGE_LEN];
    socket.read(buffer, IPCSocket::MAX_MESSAGE_LEN);
    out << buffer;
    return out;
}
