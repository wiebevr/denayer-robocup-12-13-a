// Includes:
//#include "ipc/ipc_server.h"

#include "low_level.h"

// Standard:
#include <iostream>
#include <stdlib.h>

// ---------------------------------------------------------------------------
int main(int argc, char **argv)
{
//    IPCServer strategy(IPCSocket::WIFI_STRATEGY);
//    strategy.open();
    
//    char buffer[IPCSocket::MAX_MESSAGE_LEN];
    int length;
    LowLevel * ll = new LowLevel();
    //for( int i = 0; i < 100000; i++) 
       // ll->stopMoving();
    char a = 'b';
    while (a != 'q')
    {
        std::cout << "Niets doen!" << std::endl;
        std::cin >> a; 
        switch(a)
        {
            case 'f':   ll->driveForward(10); break;
            case 'b':   ll->driveBackwards(10); break;
            case 'r':   ll->turnRight(10); break;
            case 'l':   ll->turnLeft(10); break;
            case 'a':   ll->ledTest(); break;
            case 's':   ll->stopMoving(); break;
        }

    }
    ll->stopMoving();

    return 0;
}
