/*********************************************************************************************************
*
* @brief The test main program to test the wifi server program. The wifi server runs on the external
*        computer
* @author Maarten Vandersteegen
* @date 03-2012
*
*********************************************************************************************************/

#include <iostream>
#include "wifiserver.h"
#include "log.h"

using namespace std;

/*********************************************************************************************************
*
*      Main test program
*
*********************************************************************************************************/

int main(int argc, char* argv[])
{
       Log *l=new Log("Test_wifiserver");
       l->stuur("init from main");
       cout<<"starting test main wifi server! \n";

       Wifiserver *server;
       server = Wifiserver::getInstance();       //allocate singleton instance
       server->start();                          //start the internal thread

       VisionData data;

       int i=0;                                  //just a test variable

       while(1)
       {
              i++;                                      //something to change the coordinates in time to make a nicer demo :)

              //Random garbage added to data
              data.robot1x =  0.1+i;	data.robot1y =  0.2+i;	data.robot1rotx =  0.3+i;	data.robot1roty =  0.4+i;
              data.robot2x = -0.1-i;	data.robot2y = -0.2-i;	data.robot2rotx = -0.3-i;	data.robot2roty = -0.4-i;
              data.ballx = 100+i;	data.bally = 200-i;
              data.goal1x = 1337+i;	data.goal1y	= 101+i;	data.goal2x	= -5-i;	data.goal2y	= -999.999+i;

              // final step: broadcast them!
              cout << "Sending " << data.toString() << endl;
              server->sendVisionData(data);                     //broadcast the game object over the wifi network
              usleep(1000000);                           //tunable loop delay (do not hesitate to make it zero!)
       }
       delete l;
       return 0;
}
