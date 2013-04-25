/*********************************************************************************************************
*
* @brief The implementation of the class Wifiserver
* @author Bart Volkaerts, Jona Gladines
* @date 04-2013
* Edited by Sven Meys @ 03-2013 to support VisionData class
*
*********************************************************************************************************/

#include "wifiserver.h"

//set the static singleton instance to zero
Wifiserver* Wifiserver::instance = NULL;

/*********************************************************************************************************
*
*      get the singleton instance
*
*********************************************************************************************************/

Wifiserver* Wifiserver::getInstance()
{
    if(instance == NULL)
    {
        instance = new Wifiserver();                    //if no instance has been made yet, allocate one
    }
    return instance;
}

/*********************************************************************************************************
*
*      constructor
*
*********************************************************************************************************/

Wifiserver::Wifiserver()
{
        l = new Log("wifi server");                     //register to the log
        sendFlag = false;

        if(init() == -1)                                //init the network
               exit(1);                                 //init failed
}

/*********************************************************************************************************
*
*      Send method
*
*      Description: The method notifies the internal thread that new data is ready for transmission.
*                   It waits for a possible pending transmission to finish before it copies the data
*                   to the transmission buffer.
*
*      Params: data is a reference to the (binary) string that has to be send
*
*********************************************************************************************************/

void Wifiserver::send(const string& data)
{
       while(sendFlag);            //wait for possible pending transmissions to finish
       in = data;                  //copy the input string to the transmission buffer
       sendFlag = true;            //notify the internal thread that new data is ready for transmission
}

/*********************************************************************************************************
*
*      Calculate CRC check
*
*      Description: The function calculates a CRC32 check from the header lib lib_crc.h on the input data
*                   The calculation time has a linear relation to the size of the input data.
*      Params: data: contains a pointer to the input data
*              size: is the length of *data in bytes
*      Return value: the function returns the CRC checksum
*
*********************************************************************************************************/

LongWord Wifiserver::CalcCRC(const char* data, const int size)
{
       LongWord crc_32 = 0xffffffffL;
       char *ptr = (char*)data;
       int i;

       for(i=0;i<size;i++)
       {
              crc_32 = update_crc_32(crc_32, *ptr);
              ptr++;
       }

       return crc_32 ^= 0xffffffffL;                    //take one's complement
}

/*********************************************************************************************************
*
*      Send Datagram
*
*      Params: data: contains a pointer to the data field,
*              size: is the length of *data in bytes
*
*********************************************************************************************************/

int Wifiserver::SendDatagram(const void* data, int size)
{
       int numbytes;

       if ((numbytes=sendto(sock, data, size, 0, \
              (struct sockaddr*)&addr_rem, sizeof(addr_rem))) == -1)
       {
              perror("Wifiserver: sendto failed");
              return -1;
       }
       return numbytes;
}

/*********************************************************************************************************
*
*      Send Packet
*
*      Description:
*      ------------
*
*      The function packs input data into a frame and broadcasts the frame over the network
*      The frame contains the following fields:
*       _________________________________________________________
*      |  seq nr  |  length  | input data ...    ... | CRC check |
*
*    - seq nr: A sequence number is embedded in each packet. The sequence number is 4 bytes
*      long, and large enough to prevent wrapping around.
*
*    - length: Number of bytes in the input data field. The length is 4 bytes.
*
*    - input data: the input data. The data is byte oriented and can contain any data.
*
*    - CRC check: A CRC32 check is calculated on the entire frame (all flieds included)
*      The CRC32 checksum is 4 bytes long.
*
*      Function IO:
*      ------------
*
*      Params: data: contains a pointer to the input data
*              size: is the length of *data in bytes
*
*      The return value represents the number of transmitted bytes (including the bytes of all fields).
*      If the return value is -1, there's something wrong with the transmission
*      (bad socket or something like that).
*
*********************************************************************************************************/

int Wifiserver::SendPacket(const void* data, int size)
{
	   LongWord idx=0;
       LongWord crc;
       static char outbuf[OUTBUFLEN];
       static LongWord seq_nr=1;     //sequence number (initial value = 1)

       LongWord buffer;

       //copy sequence number to output frame (4 bytes)
       buffer = htonl(seq_nr);
       memcpy(&outbuf[idx], &buffer, sizeof(LongWord));
       idx += sizeof(LongWord);
       seq_nr++;

       //copy size to output frame (4 bytes)
       buffer = htonl (size);
       memcpy(&outbuf[idx], &buffer, sizeof(LongWord));
       idx += sizeof(LongWord);

       //copy all the input data to the output frame
       memcpy(&outbuf[idx], data, size);
       idx += size;

       //calculate and add CRC32 check
       buffer = htonl(CalcCRC(outbuf, idx));
       memcpy(&outbuf[idx], &buffer, sizeof(LongWord));
       idx += sizeof(LongWord);

       //send the frame over the network
       return SendDatagram(outbuf, idx);
}

/*********************************************************************************************************
*
*      Init routine for the network
*
*********************************************************************************************************/

int Wifiserver::init()
{
       int broadcast = 1;

       //get the host info of the listener host(s)
       /*if ((remhost = gethostbyname(IPV4)) == NULL)
       {
              perror("Wifiserver: init: gethostbyname failed");
              return(-1);
       }*/

       //fill in the address from the listener(s)
       //this is the address we will send our datagram packets to
       memset(&addr_rem, 0, sizeof(addr_rem));
       addr_rem.sin_family = AF_INET;
       //addr_rem.sin_addr = *((struct in_addr*)remhost->h_addr);
       addr_rem.sin_addr.s_addr = inet_addr("255.255.255.255");
       addr_rem.sin_port = htons(UDPPORT);              //UDP port

       //create the socket to send from (socket of this host)
       if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       {
              perror("Wifiserver: init: create socket failed");
              return(-1);
       }

       //this call is what allows broadcast packets to be sent: if this is omitted,
       //sending to a broadcast address will give an error
       if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) == -1)
       {
              perror("Wifiserver: init: setsockopt (SO_BROADCAST) failed");
              return(-1);
       }

       return 0;
}

/*********************************************************************************************************
*
*      Thread program
*
*********************************************************************************************************/

void Wifiserver::run()
{
       int res;

       while(1)
       {
              if(sendFlag)
              {
                     res = SendPacket(in.c_str(), in.size());
                     //cout << "number of bytes transmitted: " << res << endl;
                     sendFlag = false;           //done!
              }
       }
       delete l;
       close(sock);
}
