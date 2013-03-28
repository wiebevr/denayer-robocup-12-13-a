/*****************************************************************************************************//**
*
* @class Wificlient
* @brief This is the wifi client thread that runs on the robot.
* @author Maarten Vandersteegen
* @date 03-2012
*
* @section DESCRIPTION
*      Wificlient is a singleton class (only 1 instance allowed). The class contains the client thread
*      that picks broadcasted datagram pakkets from the wifi network. For a documented example on how to
*      use the wificlient see the test_client.cpp file.
*
* @section NETWORK
*      It listens on a given port number, on the "any" address. This means that every packet with the
*      correct port number that arrives on any active network interface card (wifi adaptor, ethernet card,...)
*      is received.
*      For example: PORT = 8000, we have 2 interfaces: NIC0 with IP 192.168.1.2, netmask = 255.255.255.0
*                                                      NIC1 with IP 192.168.1.3, netmask = 255.255.255.0
*
*      The following packets will be received:         Packet with dest IP = 192.168.1.2,    port = 8000
*                                                      Packet with dest IP = 192.168.1.3,    port = 8000
*                                                      Packet with dest IP = 192.168.1.255,  port = 8000
*                                                      Packet with dest IP = 255.255.255.255,port = 8000
*
* @section COMMUNICATION FRAME FORMAT IN UDP PACKET
*       _________________________________________________________
*      |  seq nr  |  length  | input data ...    ... | CRC check |
*
*    - seq nr: A sequence number is embedded in each packet. The sequence number is 4 bytes
*      long, and large enough to prevent wrapping around.
*
*    - length: Number of bytes in the input data field. The length is 4 bytes long.
*
*    - input data: the input data. The data is byte oriented and can contain any data.
*
*    - CRC check: A CRC32 check is calculated on the entire frame (all flieds included)
*      The CRC32 checksum is 4 bytes long.
*
*********************************************************************************************************/

#ifndef WIFIclient_H
#define WIFIclient_H

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
#include "../../../image_processing/public data/vision_data.h" // TODO fix path
#include "lib_crc.h"
#include "thread.h"
#include "log.h"

#define       UDPPORT       12345                       //port number where the client is listening
#define       INBUFLEN      2048                        //max number of bytes in the receive buffer for 1 packet
#define       QUEUESIZE     10                          //number of payload packets that the queue can hold

/**
* @brief This typedef must be a typedef that represents 4 bytes on the machine
* This is important for the receiver to receive correctly
*/
typedef       unsigned long LongWord;

using namespace std;

//the class is derived from the Thread class
class Wificlient : public Thread
{
       //this is private scope
       /**
       * @brief pointer to Static object (points to the single object of this singleton class)
       */
       static Wificlient* instance;
       /**
       * @brief private contructor to initialize the singleton instance
       */
       Wificlient();

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
       static Wificlient* getInstance();
       /**
       * @brief receive method. Call this method with a reference to a string to get the received payload.
       *        The method returns 'true' when data contains new received data. When the method returns
       *        false, data is left unchanged. When working with the google protocol buffers, one should
       *        call the receivePB() method. This method already implements de-serialization of the google
       *        protocol bytestream and is a bit faster than using the receive() method and doing the de-
       *        serialization manually.
       */
       bool receive(string &data);
       /**
       * @brief receivePB receives a binary payload and interpretes it as a serialized google protocol
       *        buffer bytestream. The receiver de-serializes the payload to a Game object.
       *        The operation of the method is similar to the receive() method. When a new Game object
       *        has been received, the method returns true and the parameter 'game' will contain the new
       *        data. When the method returns false, game is left unchanged.
       */
       bool receiveVisionData(VisionData &visionData);

       private:

       //functions
       int init();
       int ReceiveDatagram(void *out);
       LongWord CalcCRC(const char* data, int size);
       int ReceivePacket(string *result);

       //socket
       int sock;
       struct sockaddr_in cliAddr;                      //client address
       struct sockaddr_in servAddr;                     //client address

       //log output
       Log *l;

       //receive queue for the payload
       string queue[QUEUESIZE];
       int wp, rp;                                      //read and write pointer
};

#endif	/* WIFIclient_H */
