/*
* Author: Mathieu Theerens
*/

#ifndef BALLS_H_
#define BALLS_H_
/**
        \class Ball
        \brief Retrieves the coordinates of the ball.
        \author Mathieu Theerens
*/


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "DataCircle.h"

using namespace cv;
using namespace std;

class Ball
{
        public:
		Ball(); // Constructor of the class, does nothing except making an 
		Point2f getCoords(Mat img);
		/*	This function takes an image as input and returns the coordinates
		*	of the ball, if there is one in the image. Otherwise it returns an
		*	empty Point2f parameter.
		*/

        private:
		Mat image;
};

#endif

