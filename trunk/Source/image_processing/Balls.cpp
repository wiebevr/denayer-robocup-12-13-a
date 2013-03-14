/*
*	Author: Mathieu Theerens
*	Description: Deze functie zal de bal detecteren en het middenpunt ervan
*			 als output terugsturen
*/

#include "Balls.h"

// --------------------------------------
VisionBall::VisionBall() {}  
   
// -------------------------------------- 
Point2f VisionBall::getCoords( Mat img )
{
	image = img;
      	Mat hsv;
	cvtColor(image, hsv, CV_RGB2HSV);
	
	//imshow("hsv", hsv);

	// Met deze range kunnen we de bal detecteren
	Mat bw;
	inRange(hsv, Scalar(110, 210, 110), Scalar(120, 255, 255), bw);

	// We zoeken naar contouren in de foto, deze stellen de bal(len) voor
	vector<vector<Point> > contours;
	findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	// Deze parameters gaan we gebruiken om het midden van de cirkel te vinden
	DataCircle dc(contours);
	
	vector<Point2f> center = dc.getCenters();
	
	if ( center.size() > 0 )
		return center[0];
	else
	{
		Point2f x;		
		return x;
	}
}


