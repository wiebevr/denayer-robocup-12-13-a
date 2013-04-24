#include <iostream>
#include "vision.h"
#include "wifiserver.h"
#include "../shared/log.h"
#include "../shared/vision_data.h"

using namespace std;

/*********************************************************************************************************
*
*      Main program
*
*********************************************************************************************************/

int main(int argc, char* argv[])
{
       Log *l = new Log("Test_wifiserver");
       l->stuur("init from main");
       cout<<"starting test main wifi server! \n";

       Wifiserver *server;
       server = Wifiserver::getInstance();       //allocate singleton instance
       server->start();                          //start the internal thread

       Vision vision;
       VisionData data;

       while(1)
       {
    	   const VisionData &data = vision.fetchData();

           // final step: broadcast them!
           cout << "Sending " << data.toString() << endl;
           server->send(data.toString());             //broadcast the game object over the wifi network
           usleep(1000000);                           //tunable loop delay (do not hesitate to make it zero!)
       }
       delete l;
       return 0;
}
