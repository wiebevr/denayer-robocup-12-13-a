#include "vision.h"

//VideoCapture cap;
//Mat img;
//VisionField field;
//VisionData data;



//------------------------------------------------------------------------------

Vision::Vision() : field(initCamera(), 500, 500, 50), data() 
{
    init("/dev/video");
}

//------------------------------------------------------------------------------

Vision::Vision(const string& filename) : field(initCamera(), 500, 500, 50), data() 
{
    init(filename);
}

//------------------------------------------------------------------------------

void Vision::init(const string& filename) 
{
    cout << "[Vision::init] initializing Vision" << endl;
    Vector<Point2f> pnt = field.getPixelGoal();
    this->data.goal1x = pnt[0].x;
    this->data.goal1y = pnt[0].y;
    this->data.goal2x = pnt[1].x;
    this->data.goal2y = pnt[1].y;
    
    namedWindow( "Overview field", CV_WINDOW_AUTOSIZE );
}

Mat Vision::initCamera()
{
    cap = VideoCapture(0);
    if (!cap.isOpened()) {
        cout << "[Vision::initCamera] device already in use" << endl;
        exit(EXIT_FAILURE);
    }
    cap >> img;
    return img;
}



//------------------------------------------------------------------------------

VisionData &Vision::fetchData() 
{
    cout << "[Vision::fetchData] get data from images" << endl;
    
    Mat tmp;

    // Get new camera frame
    cap >> img;

    // Get transformed image and put it in tmp image
    field.getCorrectedImage(img).copyTo(tmp);

    // Gets ball coordinates from tmp and put it in data 
    Ball ball;
    Point2f pnt = ball.getCoords(tmp);
    pnt = field.getCoordinate(pnt);
    cout << "!!![TEST] -> " << pnt << endl;
    this->data.ballx = pnt.x;
    this->data.bally = pnt.y;

    // Get coordinates from robot 1
    Robot robot;

    pnt = robot.getCoords(tmp);
    this->data.robot1x = pnt.x;
    this->data.robot1y = pnt.y;

    // Get rotation from robot 1

    data.angle2cart(robot.getRotation(), 1);
    
    
    // draw user info
    rectangle(tmp, Point2f(50, 50), Point2f(550, 550), Scalar(0, 255, 0), 1);
    for (int i = 1; i < 4; i++) 
    {
        line(tmp, Point2f(50, (((500 / 4) * i) + 50)), Point2f(550, (((500 / 4) * i) + 50)), Scalar(0, 255, 0), 1);
        line(tmp, Point2f((((500 / 4) * i) + 50), 50), Point2f((((500 / 4) * i) + 50), 550), Scalar(0, 255, 0), 1);
    }
    circle(tmp, Point2f(50, 50), 3, Scalar(0, 255, 0));
    circle(tmp, Point2f(50, 550), 3, Scalar(0, 255, 0));
    circle(tmp, Point2f(550, 50), 3, Scalar(0, 255, 0));
    circle(tmp, Point2f(550, 550), 3, Scalar(0, 255, 0));

    line(tmp, field.getPixelGoal()[0], field.getPixelGoal()[1], Scalar(255, 255, 0), 1);
    circle(tmp, field.getPixelGoal()[0], 3, Scalar(255, 255, 0));
    circle(tmp, field.getPixelGoal()[1], 3, Scalar(255, 255, 0));

    putText(tmp, "(0, 0)", Point2f(550, 550), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
    putText(tmp, "(1, 0)", Point2f(50, 550), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
    putText(tmp, "(0, 1)", Point2f(550, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
    putText(tmp, "(1, 1)", Point2f(50, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));

    putText(tmp, "Goal 1", field.getPixelGoal()[0], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 0));
    putText(tmp, "Goal 2", field.getPixelGoal()[1], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 0));
    
    circle(tmp, Point2f(data.ballx, data.bally), 3, Scalar(0, 255, 255));
    
    circle(tmp, Point2f(data.robot1x, data.robot1y), 3, Scalar(0, 255, 255));
    line(tmp, Point2f(data.robot1x, data.robot1y), Point2f(data.robot1x + data.robot1rotx, data.robot1y + data.robot1roty), Scalar(0, 255, 255), 1);

    imshow("Overview field", tmp);

    return data;
}