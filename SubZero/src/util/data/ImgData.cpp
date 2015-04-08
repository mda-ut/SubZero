/*
 * ImgData.cpp
 *
 *  Created on: Mar 29, 2015
 *      Author: ahsueh1996
 */

#include "ImgData.h"

ImgData::ImgData(std::string ID, cv::Mat img) {
	this->imgID = ID;
	this->img = img;
}

cv::Mat* ImgData::getImg() {

}
