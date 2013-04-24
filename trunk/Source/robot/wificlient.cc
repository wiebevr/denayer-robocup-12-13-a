/*********************************************************************************************************
*
* @brief The implementation of the class Wificlient
* @author Maarten Vandersteegen
* @date 03-2012
*
*********************************************************************************************************/

#include "wificlient.h"

//set the static singleton instance to zero
Wificlient* Wificlient::instance = NULL;

/*********************************************************************************************************
*
*      get the singleton instance
*
*********************************************************************************************************/

Wificlient* Wificlient::getInstance()
{
    if(instance == NULL)
    {
        instance = new Wificlient();                    //if no instance has been made yet, allocate one
    }
    return instance;
}

/*********************************************************************************************************
*
*      constructor
*
*********************************************************************************************************/

Wificlient::Wificlient()
{
        l = new Log("wifi client");                      //register to the log
        wp = 0;                                          //reset read and write pointer from the queue
        rp = 0;                                          //the queue is actual a circular buffer

        if(init() == -1)                                 //init
        {
               cout << "Wificlient: init failed" << endl;
               exit(1);                                 //init failed
        }
}


/*********************************************************************************************************
*
*      Receive method
*
*      Description:
*      This method retrieves the data from the receiver queue. It makes a copy from a queue element to
*      the reference string, given by the caller. This way, the caller doesn't has to worry about
*      data that for example suddenly changes during processing becouse the queue has wrapped around.
*
*      Params: data is a reference to the input (binary) string that will contain the received result
*      The return value is true when new data has been received.
*
*********************************************************************************************************/

bool Wificlient::receive(string &data)
{
       if(wp != rp)
       {
              data = queue[rp];                         //copy the queue element to the reference
                                                        //this copies the whole payload

              if(rp == QUEUESIZE-1)                     //increment read pointer
                     rp = 0;
              else
                     rp++;

              return true;                              //flag that the data pointer has been updated
       }
       else
       {
              return false;
       }
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

LongWord Wificlient::CalcCRC(const char* data, int size)
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
*      Receive Datagram
*
*      Params: out: pointer where the function writes its received output to.
*
*      The function returns the number of received bytes.
*      The function returns -1 if it is not able to receive (wrong settings or someting like that)
*
*********************************************************************************************************/

int Wificlient::ReceiveDatagram(void *out)
{
       int numbytes;
       socklen_t addr_len;

       addr_len = sizeof(cliAddr);
       if((numbytes = recvfrom(sock, out, INBUFLEN , 0, (struct sockaddr*)&cliAddr, &addr_len)) == -1)
       {
              perror("Wificlient: cannot recvfrom");
              return -1;
       }

       return numbytes;
}

/*********************************************************************************************************
*
*      Receive Packet
*
*      Description:
*      ------------
*
*      The function receives datagram packets on the specified UDP port. It checks the data
*      integrity by doing a CRC check. If the CRC check is OK it checks if the sequence number in the
*      packet is greater than the previous received sequence number. If this is the case, the function
*      returns with the payload data from the data field of the packet.
*      If the CRC check fails or the sequence number is wrong, the function discards the packet and
*      continues to listen to incoming packets. A CRC check error or a wrong sequence number will be re-
*      ported to the log.txt file.
*
*      The received frame format:
*      --------------------------
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
*      The CRC32 checksum is 4 bytes long, big endian.
*
*      Function IO:
*      ------------
*
*      Params: result: restult reference to the received payload data
*      The function returns -1 if it is not able to receive (wrong settings or someting like that)
*      A return value of 0 is normal
*
*********************************************************************************************************/

int Wificlient::ReceivePacket(string *result)
{
       static char inbuf[INBUFLEN];
       static long seq_nr_prev=0;
       long crc, crc2, seq_nr;
       int numbytes, idx, size;
       long buffer;
       while(1)
       {
              //receive UDP packet
              if((numbytes = ReceiveDatagram(inbuf)) == -1)
                     return -1;

              //calculate the checksum on the received data and compare with the received checksum
              idx = numbytes - sizeof(long);
              crc = CalcCRC(inbuf, idx);
              memcpy( &buffer, &inbuf[idx], sizeof(long));
              crc2 = ntohl(buffer);

              if(crc == crc2)
              {
                     idx = 0;
                     //extract the sequence number from the packet
                     memcpy(&buffer, &inbuf[idx], sizeof(long));
                     seq_nr = ntohl(buffer);

                     idx += sizeof(long);
                     //check if the sequence number is valid
                     if(seq_nr > seq_nr_prev)
                     {
                            seq_nr_prev = seq_nr;       //update seq number

                            //extract the length of the payload
                            memcpy(&buffer, &inbuf[idx], sizeof(long));
                            size = ntohl(buffer);
                            idx += sizeof(long);

                            //extract the payload
                            result->assign(&inbuf[idx], size);

                            //done!
                            return 0;
                     }
                     else
                     {
                           //report to the log file that the sequence number is wrong
                           l->stuur("Old sequence number! packet dropped -> ej gast, stopt is me ouwe rommel te sturen!");
                     }
              }
              else
              {
                     //report to the log file that the CRC check has failed
                     l->stuur("CRC32 check failed! packet dropped -> t'is kapot :(");
              }
       }
}

/*********************************************************************************************************
*
*      Init routine for the network
*
*********************************************************************************************************/

int Wificlient::init()
{
       //fill up the client address fields
       servAddr.sin_family = AF_INET;
       servAddr.sin_addr.s_addr = htonl(INADDR_ANY);           //listen the ANY anddress
       servAddr.sin_port = htons(UDPPORT);

       //create an UDP socket
       if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       {
              perror("Wificlient: init: creating socket failed");
              return -1;
       }

       //bind the local client port to the socket
       if(bind(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) == -1)
       {
              perror("Wificlient: cannot bind port number");
              return -1;
       }
       return 0;
}

/*********************************************************************************************************
*
*      Thread program
*
*********************************************************************************************************/

void Wificlient::run()
{
       while(1)
       {
              if(ReceivePacket(&queue[wp]) == -1)       //receive datagram packet in buffer
              {
                     cout << "Wificlient: receiving failed" << endl;
                     exit(1);                          //cannot receive
              }
              if(wp == QUEUESIZE-1)                     //increment write pointer
                     wp = 0;
              else
                     wp++;
       }
       close(sock);
       delete l;
}
