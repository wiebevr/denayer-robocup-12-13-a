#include "vision.h"

VideoCapture cap;
Mat img;

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
}

VisionData Vision::fetchData()
{
	
}