#include <string>
#include <sstream>
#include "vision_data.h"

//------------------------------------------------------------------------------
VisionData::VisionData()
{
    robot1x = 0;
    robot1y = 0;
    robot1rotx = 0;
    robot1roty = 0;

    robot2x = 0;
    robot2y = 0;
    robot2rotx = 0;
    robot2roty = 0;

    // REMINDER: robot variables converten to array

    ballx = 0;
    bally = 0;

    goal1x = 0;
    goal1y = 0;
    goal2x = 0;
    goal2y = 0;

}

//------------------------------------------------------------------------------
void VisionData::angle2cart(float angle, int robot = 0)
{
	float toSmall = 0.0001;
    switch (robot)
    {
        case (2):
            //polarToCart(1, angle, this->robot2rotx, this->robot2rotx, 0);
			robot2rotx = cos( angle * PI / 180 );
			robot2roty = sin( angle * PI / 180 );
			if (robot2rotx < toSmall && robot2rotx > -toSmall ) robot2rotx = 0;
			if (robot2roty < toSmall && robot2roty > -toSmall ) robot2roty = 0;
            //cout << "   [VisionData::angle2StopidStrategie] robot 2 -> angle: " << angle \
			<< " cardisaans values: [" << robot2rotx << ", " << robot2roty << "]" << endl;
            break;
        case (1):
        default:
			robot1rotx = cos( angle * PI / 180 );
			robot1roty = sin( angle * PI / 180 );
			if (robot1rotx < toSmall && robot1rotx > -toSmall ) robot1rotx = 0;
			if (robot1roty < toSmall && robot1roty > -toSmall ) robot1roty = 0;
            //polarToCart(1, angle, this->robot1rotx, this->robot1rotx, 0);
            //cout << "   [VisionData::angle2StopidStrategie] robot 1 -> angle: " << angle \
			<< " cardisaans values: [" << robot1rotx << ", " << robot1roty << "]" << endl;
    }
}

//------------------------------------------------------------------------------
/**
 * @brief toString Serialiseert dit object tot een string
 * 		om makkelijk over het netwerk te versturen
 */
string VisionData::toString() const
{
	stringstream ss;
	ss 	<<	robot1x 	<< ' '
		<<	robot1y 	<< ' '
		<<	robot1rotx 	<< ' '
		<<	robot1roty 	<< ' '

		<<	robot2x 	<< ' '
		<<	robot2y 	<< ' '
		<<	robot2rotx 	<< ' '
		<<	robot2roty 	<< ' '

		<<	ballx 		<< ' '
		<<	bally 		<< ' '

		<<	goal1x 		<< ' '
		<<	goal1y 		<< ' '
		<<	goal2x 		<< ' '
		<<	goal2y 		<< ' ';
	return ss.str();
}

void VisionData::fromString(string& str)
{
	istringstream iss(str);
	iss >> robot1x 	>> robot1y 	>> robot1rotx >> robot1roty
		>> robot2x 	>> robot2y 	>> robot2rotx >> robot2roty
		>> ballx 	>> bally
		>> goal1x	>> goal1y
		>> goal2x	>> goal2y;
}

bool VisionData::operator==(const VisionData &rhs)
{
    if (this == &rhs) return true;  // Check for self-assignment!
    return   (robot1x == rhs.robot1x) &&
			 (robot1y == rhs.robot1y) &&
			 (robot1rotx == rhs.robot1rotx) &&
			 (robot1roty == rhs.robot1roty) &&
			 (robot2x == rhs.robot2x) &&
			 (robot2rotx == rhs.robot2rotx) &&
			 (robot2y == rhs.robot2y) &&
			 (robot2roty == rhs.robot2roty) &&
			 (ballx == rhs.ballx) &&
			 (bally == rhs.bally) &&
			 (goal1x == rhs.goal1x) &&
			 (goal1y == rhs.goal1y) &&
			 (goal2x == rhs.goal2x) &&
			 (goal2y == rhs.goal2y);
}
bool VisionData::operator!=(const VisionData &rhs)
{
	return !(operator==(rhs));
}
