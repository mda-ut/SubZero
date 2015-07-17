/*
 * ImgData.cpp
 *
 *  Created on: Mar 29, 2015
 *      Author: ahsueh1996
 */

#include <stdlib.h>
#include <stdio.h>
#include "ImgData.h"


/* ==========================================================================
 * CONSTRUCTOR & DESTRUCTOR
 * ==========================================================================
 */

ImgData::ImgData(std::string dataID,cv::Mat img) : Data(dataID) {
    this->img = img;
}

ImgData::~ImgData() {
    this->img.release();
    delete logger;
}

/* ==========================================================================
 * FRIEND FUNCS
 * ==========================================================================
 */

void ImgData::setID(std::string newID) {
	this->dataID = newID;
}



void ImgData::setImg(cv::Mat newImg) {
    this->img = newImg;
}

/* ==========================================================================
 * IMG MANIPULATION FUNCS
 * ==========================================================================
 */

cv::Mat ImgData::getImg() {
	return this->img;
}

int ImgData::getHeight() {
    return this->img.rows;
}

int ImgData::getWidth() {
    return this->img.cols;
}

void ImgData::showImg(std::string windowName) {
    if (!this->img.empty()) {
		try {
			if (windowName != "") {
				cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);
                cv::imshow(windowName,this->img);
                cv::waitKey(1);
				this->windowName = windowName;
			} else {
				cv::namedWindow(this->dataID,CV_WINDOW_AUTOSIZE);    //Create window
                cv::imshow(this->dataID,this->img);   //Show image frames on created window
                cv::waitKey(1);
                this->windowName = this->dataID;
			}
		} catch (cv::Exception) {
            logger->warn("Unable to show \""+this->dataID+"\"'s img, cv::exception");
		}
	}
}

void ImgData::closeImg() {
	cv::namedWindow(this->dataID);
    cv::namedWindow(windowName);
	cv::destroyWindow(windowName);
	cv::destroyWindow(this->dataID); //Destroy Window
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

ImgData& ImgData::operator=(const ImgData& rhs) {
    Data::operator=(rhs); //implicitly generated operator=
    this->img = rhs.img.clone();
    return *this;
}

ImgData::ImgData(const ImgData& copy) : Data(copy) {
    this->img = copy.img.clone();
}
