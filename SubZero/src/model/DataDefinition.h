/*
 * dataDefinition.h
 *
 *  Created on: Feb 28, 2015
 *      Author: ahsueh1996
 */

#ifndef DATADEFINITION_H_
#define DATADEFINITION_H_
#include <cv.h>
#include <highgui.h>
#include <string.h>


class CamData {
public:
	cv::Mat * rawImg;
	std::string msg;
	void crop(int height, int width);
};

class FPGAData {
public:
	double depth, yaw, speed;
	std::string msg;
};
