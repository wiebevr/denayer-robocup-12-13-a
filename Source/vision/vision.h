/**
 * @file vision.h
 * @classe Vision
 * @author Den Dooven Raphael
 *
 * @brief
 * Omkoepelende classe voor het vision
 *
 *
 */

#ifndef VISION_H
#define VISION_H

#define MT_FC_DEBAYER

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>

#include <iostream>

#include "../shared/vision_data.h"
#include "vision_field.h"
#include "vision_robot.h"
#include "vision_DataCircle.h"
#include "vision_balls.h"

#define width 500
#define height 500
#define border 50

using namespace std;
using namespace cv;

class Vision
{
	private:
		VideoCapture cap;
		Mat img;
		VisionField field;
		VisionData data;
            
                void init();
                Mat initCamera(const string& filename);
                void drawUserInfo(Mat tmp);
		
	public:
		Vision();
		Vision(const string& filename);
		
		VisionData &fetchData();
	
};

#endif // VISION__H
