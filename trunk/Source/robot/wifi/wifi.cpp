#include "wifi.h"

// --------------------------------------------------------------------------
Wifi::Wifi()
{
    VisionData vision_data;

    vision_data.robot1x = 0.5;
    vision_data.robot1y = 0.5;
    vision_data.robot1rotx = 0.5;
    vision_data.robot1roty = 0.5;

    vision_data.robot2x = 0.6;
    vision_data.robot2y = 0.6;
    vision_data.robot2rotx = 0.6;
    vision_data.robot2roty = 0.6;

    vision_data.ballx = 0.7;
    vision_data.bally = 0.7;

    vision_data.goal1x = 0.8;
    vision_data.goal1y = 0.8;
    vision_data.goal2x = 0.8;
    vision_data.goal2y = 0.8;

    sendVisionData(vision_data);
}

// --------------------------------------------------------------------------
Wifi::~Wifi()
{

}

// --------------------------------------------------------------------------
void Wifi::sendVisionData(const VisionData &vision_data)
{
    ofstream outfile("game.pb");
    
    outfile << vision_data.robot1x << endl;
    outfile << vision_data.robot1y << endl;
    outfile << vision_data.robot1rotx << endl;
    outfile << vision_data.robot1roty << endl;

    outfile << vision_data.robot2x << endl;
    outfile << vision_data.robot2y << endl;
    outfile << vision_data.robot2rotx << endl;
    outfile << vision_data.robot2roty << endl;

    outfile << vision_data.ballx << endl;
    outfile << vision_data.bally << endl;

    outfile << vision_data.goal1x << endl;
    outfile << vision_data.goal1y << endl;
    outfile << vision_data.goal2x << endl;
    outfile << vision_data.goal2y << endl;

    outfile.flush();
    outfile.close();
}

//VisionData Wifi::receiveVisionData()
//{
//}
