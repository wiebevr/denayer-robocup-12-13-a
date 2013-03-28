#include "wifi/wifi.h"
#include "../shared/vision_data.h"
#include "wificlient.h"
#include "strategy.h"
#include "log.h"

int main(int argc, char **argv)
{
    Wifi wifi();
    Strategy strategy();

    Log *l=new Log("Test_wificlient");
    l->stuur("init from main");
    cout<<"starting test main wifi client! \n";

    Wificlient *client;
    client = Wificlient::getInstance();       //allocate singleton instance
    client->start();                          //start the thread

    VisionData data;

    while(1)
    {
           if(client->receiveVisionData(data))
           {
                  //print some data
         	  	cout << "Data packet received: object contents = " <<  data.toString() << endl;
         	    strategy.setCoords(&data);
         	    strategy.run();
           }
    }
    delete l;
    return 0;
}
