/*
*	Author: Mathieu Theerens
*	Deze klasse helpt me in het berekenen van de middenpunten en
*	radii	
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class DataCircle{
        public:
		DataCircle(vector<vector<Point> > cnt);
		void calcData();
		vector<Point2f> getCenters();
		vector<float> getRadius();
		
        private:
        	vector<vector<Point> > contours;
	 	vector<Point2f> center;
		vector<float> radius;
};
