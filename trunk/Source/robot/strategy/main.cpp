/**
	\brief Strategy main
	\author Gert Mertes
*/

/**
 *	compile with:
 *	g++ main.cpp tests/low_level.cpp tests/vision_data.cpp strategy.cpp robot.cpp kicker.cpp keeper.cpp
 *	to test
 *	./a.out >> testout
 *	to save output
 *	Don't forget mode in Strategy to switch keeper/kicker!
*/

#include <iostream>

#include "strategy.h"
using namespace std;

// ---------------------------------------------------------------------------
int main(int argc, char **argv)
{
	Strategy strat;
	VisionData *co = new VisionData();
	
	//add random data for tests here
	//all values between 0 - 1
	co->robot1x = 0.2;
     	co->robot1y = 0.2;
     	co->robot1rotx = 1;
     	co->robot1roty = 0;

    	co->robot2x = 0;
     	co->robot2y = 0;
     	co->robot2rotx = 0;
     	co->robot2roty = 0;

     	co->ballx = 0.5;
     	co->bally = 0.5;

     	co->goal1x = 1;
     	co->goal1y = 0.4;
     	co->goal2x = 1;
     	co->goal2y = 0.6;	
	
	strat.setCoords(co);
	cout << "main run" << endl;
	strat.run();
	
	exit(1);
}
