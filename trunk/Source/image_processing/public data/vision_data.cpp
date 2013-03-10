#include "vision_data.h"

float robot1x;
float robot1y;
float robot1rotx;
float robot1roty;

float robot2x;
float robot2y;
float robot2rotx;
float robot2roty;

float ballx;
float bally;

float goal1x;
float goal1y;
float goal2x;
float goal2y;

VisionData::VisionData()
{
    this->robot1x = 0;
    this->robot1y = 0;
    this->robot1rotx = 0;
    this->robot1roty = 0;

    this->robot2x = 0;
    this->robot2y = 0;
    this->robot2rotx = 0;
    this->robot2roty = 0;

    // REMINDER: robot variables converten to array

    this->ballx = 0;
    this->bally = 0;

    this->goal1x = 0;
    this->goal1y = 0;
    this->goal2x = 0;
    this->goal2y = 0;

}

void VisionData::angle2cart(float angle, int robot = 0)
{
	
    switch (robot)
    {
        case (2):
            //polarToCart(1, angle, this->robot2rotx, this->robot2rotx, 0);
			this->robot2rotx = cos( angle * PI / 180 );
			this->robot2roty = sin( angle * PI / 180 );
			if (this->robot2rotx < 0.001) this->robot2rotx = 0;
			if (this->robot2roty < 0.001) this->robot2roty = 0;
            cout << "   [VisionData::angle2StopidStrategie] robot 2 -> angle: " << angle \
			<< " cardisaans values: [" << this->robot2rotx << ", " << this->robot2roty << "]" << endl;
            break;
        case (1):
        default:
			this->robot1rotx = cos( angle * PI / 180 );
			this->robot1roty = sin( angle * PI / 180 );
			if (this->robot1rotx < 0.001) this->robot1rotx = 0;
			if (this->robot1roty < 0.001) this->robot1roty = 0;
            //polarToCart(1, angle, this->robot1rotx, this->robot1rotx, 0);
            cout << "   [VisionData::angle2StopidStrategie] robot 1 -> angle: " << angle \
			<< " cardisaans values: [" << this->robot1rotx << ", " << this->robot1roty << "]" << endl;
    }
}
