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

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>

#include <iostream>

#include "vision_field.h"
#include "vision_data.h"
#include "Robot.h"
#include "DataCircle.h"
#include "Balls.h"



using namespace std;
using namespace cv;

class Vision
{
	private:
		VideoCapture cap;
		Mat img;
		
	public:
		Vision();
		Vision(const string& filename);
		
		VisionData fetchData();
	
}