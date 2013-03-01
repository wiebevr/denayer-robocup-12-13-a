/*
* Author: Mathieu Theerens
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "images.h"

using namespace cv;
using namespace std;

class Ball{
        public:
		Ball(Mat img);
		Point2f getCoords();
		void showBalls(int, void* );

        private:
	 	char* window_dest;
		Mat image;
};
