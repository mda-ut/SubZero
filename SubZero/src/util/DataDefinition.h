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

// to be included by filter>> model >> controller also by view and HI.

class Data {

};

class ImgData : public Data {
	/* Wrapper class containing a image of the standard image type
	 * and functions to get image parameters such as dimensions,
	 * and pixel depth. Each CamData has a string ID and msg to identify
	 * the image according to the img's filtration and to carry
	 * additional information (ex. error msg in case when the img
	 * had failed to be filtered fully).
	 */
public:
	// Constructor takes in the string ID of the image being created.
	ImgData(std::string ID, cv::Mat img) {
		this->ID = ID;
		this->img = img;
	}

	// Getter for img ID
	std::string getID() {
		return this->ID;
	}

	// Getter for img data, invoker must expect the standard image type
	cv::Mat getImg() {

		return this->img;
	}

	// Getter for image height
	int getHeight() {
		return this->img;	// some opncv mat func .height();
	}

	// Getter for image width
	int getWidth() {
			return this->img;	// some opncv mat func .width();
	}

private:
	cv::Mat img;
	std::string ID;
	std::string msg;
};

class FPGAData {
public:
	double depth, yaw, speed;
	std::string msg;
};
