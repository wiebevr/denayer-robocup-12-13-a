#include "vision.h"




//------------------------------------------------------------------------------

Vision::Vision() 
        : field(initCamera("/dev/video"), HEIGHT, WIDTH, BORDER), data() 
{
    init();
}

//------------------------------------------------------------------------------

Vision::Vision(const string& filename) 
        : field(initCamera(filename), HEIGHT, WIDTH, BORDER), data() 
{
    init();
}

//------------------------------------------------------------------------------

void Vision::init() 
{
    //cout << "[Vision::init] initializing Vision" << endl;
    Vector<Point2f> pnt = field.getPixelGoal();
    this->data.goal1x = pnt[0].x;
    this->data.goal1y = pnt[0].y;
    this->data.goal2x = pnt[1].x;
    this->data.goal2y = pnt[1].y;
    
    namedWindow( "Overview field", CV_WINDOW_AUTOSIZE );
}

//------------------------------------------------------------------------------
Mat Vision::initCamera(const string& filename)
{
    cap = VideoCapture(0);
    if (!cap.isOpened()) {
        //cout << "[Vision::initCamera] device already in use" << endl;
        exit(EXIT_FAILURE);
    }
    cap >> img;
	cvtColor(img, img, CV_BayerBG2BGR);
		//img = imread("../buildHome/Img/Keeper.ppm");
		
    return img;
}

//------------------------------------------------------------------------------
void Vision::drawUserInfo(Mat tmp)
{
    // draw user info
    rectangle(tmp, Point2f(BORDER, BORDER), Point2f(BORDER + WIDTH, BORDER + HEIGHT), Scalar(0, 255, 0), 1);
    for (int i = 1; i < 4; i++) 
    {
        line(tmp, Point2f(BORDER , (((HEIGHT / 4) * i) + BORDER)), Point2f(BORDER + WIDTH, (((HEIGHT / 4) * i) + BORDER)), Scalar(0, 255, 0), 1);
        line(tmp, Point2f((((WIDTH / 4) * i) + BORDER) , BORDER), Point2f((((WIDTH / 4) * i) + BORDER), BORDER + HEIGHT), Scalar(0, 255, 0), 1);
    }
    circle(tmp, Point2f(BORDER, BORDER ), 3, Scalar(0, 255, 0));
    circle(tmp, Point2f(BORDER, HEIGHT + BORDER ), 3, Scalar(0, 255, 0));
    circle(tmp, Point2f(WIDTH + BORDER, BORDER ), 3, Scalar(0, 255, 0));
    circle(tmp, Point2f(WIDTH + BORDER, HEIGHT + BORDER ), 3, Scalar(0, 255, 0));

    line(tmp, field.getPixelGoal()[0], field.getPixelGoal()[1], Scalar(255, 255, 0), 1);
    circle(tmp, field.getPixelGoal()[0], 3, Scalar(255, 255, 0));
    circle(tmp, field.getPixelGoal()[1], 3, Scalar(255, 255, 0));

    putText(tmp, "(0, 0)", Point2f( WIDTH + BORDER, HEIGHT + BORDER ), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
    putText(tmp, "(1, 0)", Point2f( BORDER, HEIGHT + BORDER ), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
    putText(tmp, "(0, 1)", Point2f( WIDTH + BORDER, BORDER ), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
    putText(tmp, "(1, 1)", Point2f( BORDER, BORDER ), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));

    putText(tmp, "Goal 1", field.getPixelGoal()[0], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 0));
    putText(tmp, "Goal 2", field.getPixelGoal()[1], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 0));

	Point2f pos = field.getPixel(Point2f(data.ballx, data.bally));
    
    circle(tmp, pos, 3, Scalar(0, 255, 255));
    
    pos = field.getPixel(Point2f(data.robot1x, data.robot1y));

    circle(tmp, pos, 3, Scalar(0, 255, 255));
    line(tmp, pos, Point2f(pos.x + (data.robot1rotx * 10), pos.y - (data.robot1roty * 10)), Scalar(0, 255, 255), 1);

    imshow("Overview field", tmp);
}


//------------------------------------------------------------------------------

VisionData &Vision::fetchData() 
{
    //cout << "[Vision::fetchData] get data from images" << endl;
    
    Mat tmp;

    // Get new camera frame
    cap >> img;
	cvtColor(img, img, CV_BayerBG2BGR);
		//img = imread("../buildHome/Img/Keeper.ppm");

    // Get transformed image and put it in tmp image
    field.getCorrectedImage(img).copyTo(tmp);

	namedWindow("Overview field");
    // Gets ball coordinates from tmp and put it in data 
    VisionBall ball;
    Point2f pnt = ball.getCoords(tmp);
    pnt = field.getCoordinate(pnt);
    this->data.ballx = pnt.x;
    this->data.bally = pnt.y;
	
	cout << "ball: " << pnt << endl;

    // Get coordinates from robot 1
    VisionRobot robot;

    pnt = robot.getCoords(tmp);
    pnt = field.getCoordinate(pnt);
    this->data.robot1x = pnt.x;
    this->data.robot1y = pnt.y;

	cout << "robot: " << pnt << endl;

    // Get rotation from robot 1

    data.angle2cart(robot.getRotation(), 1);

	cout <<  "    rotation robot: [" << data.robot1rotx << ", " << data.robot1roty << "] - degrees: " 
	<< robot.getRotation() << "°" << endl;
    
    drawUserInfo(tmp);
    

    return data;
}
