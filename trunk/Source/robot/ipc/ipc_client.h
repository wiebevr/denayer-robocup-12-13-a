#ifndef IPC_CLIENT_H
#define IPC_CLIENT_H

#include "ipc_socket.h"


/**
    \class IPCClient
    \brief Implements client for inter process communication. */
class IPCClient : public IPCSocket
{
public:
    /** Constructor, \see \super. */
    IPCClient(Name name);

    /** Destructor. */
    virtual ~IPCClient();

    /** Starts listening for client. */
    bool open();

};
#endif // IPC_CLIENT_H
