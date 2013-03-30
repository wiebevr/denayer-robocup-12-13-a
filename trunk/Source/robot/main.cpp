#include "wificlient.h"
#include "strategy/strategy.h"

int main(int argc, char **argv)
{
    Strategy strategy;

    Log *l=new Log("Test_wificlient");
    l->stuur("init from main");
    cout<<"starting test main wifi client! \n";

    Wificlient *client;
    client = Wificlient::getInstance();       //allocate singleton instance
    client->start();                          //start the thread

    VisionData vData;
    string data;

    while(1)
    {
           if(client->receive(data))
           {
                  //print some data
        	    vData.fromString(data);
        	   	cout << "Data packet received: object contents = " <<  vData.toString() << endl;

         	    strategy.setCoords(&vData);
         	    strategy.run();
           }
    }
    delete l;
    return 0;
}
