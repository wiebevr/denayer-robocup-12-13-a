#include "wificlient.h"
#include "strategy/strategy.h"

int main(int argc, char **argv)
{
    string input = "0";
    int mode;
    cout << "kicker (0) of keeper (1)?" << endl;

    while (true) {
      getline(cin, input);

      // This code converts from string to number safely.
      stringstream myStream(input);
      if (myStream >> mode)
        break;
      cout << "Invalid number, please try again" << endl;
    }
    cout << "You entered: " << mode << endl << endl;

    Strategy strategy;
    strategy.setMode(mode);

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
