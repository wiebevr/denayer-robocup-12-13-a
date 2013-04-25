/*****************************************************************************************************//**
*
* @class Wifiserver
* @brief This is the wifi server that runs on the external computer.
* @author Bart Volkaerts, Jona Gladines
* @date 03-2012
*
*********************************************************************************************************/

#ifndef WIFIserver_H
#define WIFIserver_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
//#include "game.pb.h"
#include "../shared/lib_crc.h"
#include "../shared/thread.h"
#include "../shared/log.h"
#include <stdint.h>

#define       UDPPORT       12345         //port and IP address of the listener(s)
#define       IPV4          "sven-mba"
#define       OUTBUFLEN     2048          //max size of the output buffer containing the whole datagram frame
                                          //this includes all the fields (seq nr, length, input data, CRC check)
/**
* @brief This typedef must be a typedef that represents 4 bytes on the machine
* This is important for the receiver to receive correctly.
*/
typedef       uint32_t LongWord;

using namespace std;

//the class is derived from the Thread class
class Wifiserver : public Thread
{
       //this is private scope
       /**
       * @brief pointer to Static object (points to the single object of this singleton class)
       */
       static Wifiserver* instance;
       /**
       * @brief private contructor to initialize the singleton instance
       */
       Wifiserver();

       public:

       /**
       * @brief the actual thread. Call the start() method (implemented in thread.cpp) to start the thread
       * @sa threat.h
       */
       void run();
       /**
       * @brief get the pointer to the singleton instance so you can work with it. If no instance has
       *        been made yet, this method will create one. If this is the case, don't forget to call the
       *        start() method to start the thread!
       */
       static Wifiserver* getInstance();
       /**
       * @brief call this method to broadcast a (binary) string over the network.
       *        De method notifies the internal thread that new data is ready to be send. The method waits
       *        for a possible pending transmission to finish to avoid data loss when calling this method
       *        to fast.
       *        When working with the google protocol buffers, one should call the sendPB() method.
       *        This method already implements serialization of the google protocol bytestream and is a bit
       *        faster than using the send() method in combination with manual serialization.
       */
       void send(const string &data);

       private:

       //functions
       int init();
       int SendDatagram(const void* data, const int size);
       LongWord CalcCRC(const char* data, int size);
       int SendPacket(const void* data, int size);

       //socket variables
       int sock;
       struct sockaddr_in addr_rem;                     //listener UDP socket address
       struct hostent     *remhost;                     //listener host infromation

       //log output
       Log *l;

       string in;                                       //contains the input data that has to be send
       bool sendFlag;                                   //flag to indicate that a new packet is ready to be send
};

#endif	/* WIFIserver_H */
