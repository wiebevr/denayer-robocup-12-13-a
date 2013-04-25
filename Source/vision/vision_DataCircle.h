/*
*	Author: Mathieu Theerens
*	Deze klasse helpt me in het berekenen van de middenpunten en
*	radii	
*/

#ifndef DATACIRCLE_H_
#define DATACIRCLE_H_
/**
        \class DataCircle
        \brief Calculates centers and radii of contours.
        \author Mathieu Theerens
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class DataCircle{
        public:
		DataCircle(vector<vector<Point> > cnt);
		/**	Constructor for the class, takes a contour as input.
		*/
		
		void calcData();
		/**	This gets called automatically in the constructor, it calculates
		* 	the centers and radii corresponding to the contour given.
		*/
		
		vector<Point2f> getCenters();
		/**	With this function you can get the centers obtained in the function calcData().
		*/
		
		vector<float> getRadius();
		/**	With this function you can get the radii obtained in the function calcData().
		*/
		
        private:
        	vector<vector<Point> > contours;
	 	vector<Point2f> center;
		vector<float> radius;
};

#endif

