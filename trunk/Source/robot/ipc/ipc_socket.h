#ifndef IPC_SOCKET_H
#define IPC_SOCKET_H

// Standard C++:
#include <string>
#include <iostream>

/**
    \class IPCSocket
    \brief This class is responsible for internal communication between
        different modules on the robot. Inherited by IPCServer and IPCClient */
class IPCSocket
{
public:
    /** What socket are we? */
    enum Name
    {
        STRATEGY_LOW_LEVEL,
        WIFI_STRATEGY
    };

    /** Constructor, does not open socket, ICPSocket::open() should be
     * called before use. */
    IPCSocket(Name name);

    /** Destructor */
    virtual ~IPCSocket();

    /** Opens the connection to the other side, blocks until connection is
     * made. */
    virtual bool open() = 0;

    /** Used to write to the socket. */
    const IPCSocket &operator<<(const std::string &message);

    /** Used to read to the socket. */
    const IPCSocket &operator>>(std::string &message);

    /** Allow writing to the output stream */
    friend std::ostream& operator<< (std::ostream &out, IPCSocket &socket);

    /** Used to write to the socket. \param size is the length of the \param data buffer. */
    void write(const char *data, int size);

    /** Used to read to the socket. \param size is the length of the \param data buffer. */
    int read(char *buffer, int size);

    /** Maximum length of a message. */
    enum
    {
        MAX_MESSAGE_LEN = 1024
    };

    /** Path to the Wifi <-> Strategy socket. */
    static const char *WIFI_STRATEGY_PATH;

    /** Path to the Strategy <-> Low level socket. */
    static const char *STRATEGY_LOW_LEVEL_PATH;

protected:
    /** What socket should we use? */
    Name name;

    /** File descriptor of the socket. */
    int socket_fd;

    /** Close all open sockets. */
    void cleanUp();


};
#endif // IPC_SOCKET_H
