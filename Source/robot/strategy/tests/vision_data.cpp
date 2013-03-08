#include "vision_data.h"

/** 
 * Imposter class for testing strategy
*/

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

    this->ballx = 0;
    this->bally = 0;

    this->goal1x = 0;
    this->goal1y = 0;
    this->goal2x = 0;
    this->goal2y = 0;

}
