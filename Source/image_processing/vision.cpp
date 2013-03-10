#include "vision.h"

VideoCapture cap;
Mat img;
VisionField field;
VisionData data;

Vision::Vision()
{
	Vision::Vision(0);
}

Vision::Vision(const string& filename)
{
	cap = VideoCapture();
	if ( !cap.isOpened() )
	{
		cout << "[Vision] device already in use" <<endl;
		return -1;
	}
	cap >> img;
	
	field(img, 500, 500, 50);
	data();
	Vector<Point2f> pnt = field.getPixelGoal();
	this->data.goal1x = pnt[0][0];
    this->data.goal1y = pnt[0][1];
    this->data.goal2x = pnt[1][0];
	this->data.goal2y = pnt[1][1];
}

VisionData Vision::fetchData()
{
	Mat tmp;
	
	// Get new camera frame
	cap >> img;
	
	// Get transformed image and put it in tmp image
	field.getCorrectedImage(img).copyTo(tmp);
	
	// Gets ball coordinates from tmp and put it in data 
	Ball ball();
	Point2f pnt = ball.getCoords(tmp);
	pnt = field.getCoordinate(pnt);
	
	this->data.ballx = pnt[0];
	this->data.bally = pnt[1];
	
	// Get coordinates from robot 1
	Robot robOne();
	
	pnt = robOne.getCoords(tmp);
	this->data.robot1x = pnt[0];
	this->data.robot1y = pnt[1];
	
	// Get rotation from robot 1
	
	data.angle2cart( robOne.getRotation(), 1 );

	return data;
}