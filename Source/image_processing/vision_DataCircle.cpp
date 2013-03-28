/*
* 	Author: Mathieu Theerens
*/
#include "vision_DataCircle.h"

//------------------------------
DataCircle::DataCircle(vector<vector<Point> > cnt): contours(cnt)
{
	calcData();
}      

//------------------------------
void DataCircle::calcData()
{
	center.resize(contours.size());
	radius.resize(contours.size());
	vector<vector<Point> > contours_poly( contours.size() );

	for( int i = 0; i < contours.size(); i++ )
	{ 
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		
		// Deze functie neemt de output van approxpoly en geeft zelf als output de 
		// radius en middenpunt van de cirkels	
		minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );		
	}
}

//------------------------------
vector<Point2f> DataCircle::getCenters()
{
      return center;
}

//------------------------------
vector<float> DataCircle::getRadius()
{
      return radius;
}

