#ifndef VISION_DATA_H
#define VISION_DATA_H

class VisionData
{
public:
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

    VisionData();
};

#endif // VISION_DATA_H
