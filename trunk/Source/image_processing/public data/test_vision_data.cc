/**
 * @file test_vision_data.cc
 * @class VisionData
 * @author Sven Meys
 *
 *  @brief Test program for all the VisionData methods
 */
#include <string>
#include <sstream>
#include "vision_data.h"

using namespace std;

bool test_angle2cart();
bool test_equals();
bool test_toString();

int main()
{
	test_equals();
	test_toString();
	return 0;
}

bool test_angle2cart()
{
	cout << "Running test_angle2cart   ";
	cout << "Not implemented yet";
	// TODO
}

bool test_equals()
{
	cout << "Running test_equals       ";
	VisionData d1, d2, d3;
	d3.goal2y = 1;

	bool result = (d1 == d2 && d1 != d3);
	cout << (result ? "SUCCESS" : "FAILED") << endl;

	return result;
}

bool test_toString()
{
	cout << "Running test_toString     ";

	VisionData d1;			// Setting member variables
	d1.robot1x 		= 0.1;
	d1.robot1y 		= 0.2;
	d1.robot1rotx 	= 0.3;
	d1.robot1roty 	= 0.4;

	d1.robot2x 		= -0.1;
	d1.robot2y 		= -0.2;
	d1.robot2rotx 	= -0.3;
	d1.robot2roty 	= -0.4;

	d1.ballx		= 100;
	d1.bally		= 200;

	d1.goal1x		= 1337;
	d1.goal1y		= 101;
	d1.goal2x		= -5;
	d1.goal2y		= -999.999;

	VisionData d2;			// Generating string and using it to initialize another VisionData object
	string str = d1.toString();
	d2.fromString(str);

	// If both have the same member values, they are equal
	bool result = d1 == d2;
	cout << (result ? "SUCCESS" : "FAILED") << endl;

	return result;
}

