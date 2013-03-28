/*********************************************************************************************************
*
* @brief The test main program to test the wifi client program. The client program runs on the robots
* @author Maarten Vandersteegen
* @date 03-2012
*
*********************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include "wificlient.h"
#include "log.h"

using namespace std;

/*********************************************************************************************************
*
*      Main test program
*
*********************************************************************************************************/

int main(int argc, char* argv[])
{
       Log *l=new Log("Test_wificlient");
       l->stuur("init from main");
       cout<<"starting test main wifi client! \n";

       Wificlient *client;
       client = Wificlient::getInstance();       //allocate singleton instance
       client->start();                          //start the thread

       //////////////////////////////////////////////////////////////////////////////////////////////////
       // google protocol buffers test code
       //////////////////////////////////////////////////////////////////////////////////////////////////

       // In this test code we are going to receive a game object and unpack all coordinates.

       // fisrt step:
       // declare a Game object. You have to do this only once in the init of the program.

       VisionData data;

       while(1)
       {
              //second step: poll the receiver method to get the received data.
              //All received data is stored in a queue until you call receivePB. It will return true if data has been
              //received. The result is written to the game object.
              //For more info about the function see the Wificlient header and source file
              if(client->receiveVisionData(data))
              {
                     //print some data
            	  	 cout << "Data packet received: object contents = " <<  data.toString() << endl;
              }
       }
       delete l;
       return 0;
}
