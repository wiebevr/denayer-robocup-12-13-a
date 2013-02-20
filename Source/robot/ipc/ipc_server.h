#ifndef IPC_SERVER_H
#define IPC_SERVER_H

#include "ipc_socket.h"

/**
    \class IPCServer
    \brief Implements server for inter process communication. */
class IPCServer : public IPCSocket
{
public:
    /** Constructor, see \super. */
    IPCServer(Name name);

    /** Destructor */
    virtual ~IPCServer();

    /** Starts listening for client */
    bool open();

};
#endif // IPC_SERVER_H
