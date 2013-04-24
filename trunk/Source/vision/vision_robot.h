/*
* Author: Mathieu Theerens
*/

#ifndef ROBOT_H_
#define ROBOT_H_
/**
        \class Robot
        \brief Retrieves the coordinates and rotation of the robot.
        \author Mathieu Theerens
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include "DataCircle.h"

using namespace cv;
using namespace std;

#define PI 3.14159265
#define THRESHOLD 20
#define MAX_KERNEL_LENGTH 5
#define MAXDIST 1000000
#define MINDIST 20

class VisionRobot{
        public:
		VisionRobot(); // constructor of the class
		
		Point2f getCoords( Mat img );	
		/*	This fucntion takes an image as input and returns the coordinates of the robot.
		* 	At the moment this function only returns the coordinates of our own robot,
		*	but maybe in the future it can be expanded to also return the coordinates
		* 	of the other team's robot.
		*/
		
		Mat smoothImage( Mat img ); // This fucntion smoothes the picture, so that any remaining noise if removed
		
		Mat removeBall( Mat img, vector<vector<Point> > cnt );
		/*	This function calculates the radii of the different circles on the picture
		*	and since the circle with the biggest radius is the ball, we can easily
		*	remove it this way. After this function only the circles of the different
		*	robots remain.
		*/
		
		vector<vector<Point> > extractContourMiddle( Mat img );	
		/*	This function is used by the getCoords() function, it extracts the middle
		*	circle of the robot, so that we can easily calculate distances to this circle.
		*/
			
		void calcRotation( vector<vector<Point> > mcontour, vector<vector<Point> > allcontours );
		/*	This function calculates the rotation of the robot, it uses the atan2 math function
		* 	for this.
		*/
		
		float getRotation(); 
		/*	This function returns the rotation calculated with calcRotation,
		* 	the returned rotation lies between -180 and + 180 degrees.
		*/
		
		float calcDistance(Point2f a, Point2f b);
		/*	This function is used to calculate the distances between 2 points on the image
		*/

        private:
		Mat image;
		float rotation;
};

#endif

