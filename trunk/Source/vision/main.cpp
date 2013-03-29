#include "vision/vision.h"
#include "wifiserver.h"
#include "../public/vision_data.h"

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

       while(1)
       {
    	   const VisionData &data = vision.fetchData();

           // final step: broadcast them!
           cout << "Sending " << data.toString() << endl;
           server->sendVisionData(data);                     //broadcast the game object over the wifi network
           usleep(1000000);                           //tunable loop delay (do not hesitate to make it zero!)
       }
       delete l;
       return 0;
}
