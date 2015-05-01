/*
 * ImgData.cpp
 *
 *  Created on: Mar 29, 2015
 *      Author: ahsueh1996
 */

#include "ImgData.h"


/* ==========================================================================
 * CONSTRUCTOR & DESTRUCTOR
 * ==========================================================================
 */

ImgData::ImgData(std::string dataID, cv::Mat* img) {
	this->dataID = dataID;
	this->img = img;
}

ImgData::~ImgData() {
	this->img->release();
}

/* ==========================================================================
 * FRIEND FUNCS
 * ==========================================================================
 */

void ImgData::setID(std::string newID) {
	this->dataID = newID;
}

void ImgData::setImg(cv::Mat* newImg) {
	this->setImg(newImg,0);
}

void ImgData::setImg(cv::Mat* newImg,int type) {
	if (type == 0)
		this->img->release();
	this->img = newImg;
}

/* ==========================================================================
 * IMG MANIPULATION FUNCS
 * ==========================================================================
 */

cv::Mat* ImgData::getImg() {
	return this->img;
}

int ImgData::getHeight() {
	return this->img->size[0];
}

int ImgData::getWidth() {
	return this->img->size[1];
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

ImgData& ImgData::operator =(ImgData& rhs) {
	return new ImgData(rhs);
}

ImgData::ImgData(const ImgData& obj) {
	this->dataID = obj.dataID;
	this->msg = obj.msg;
	this->img = (cv::Mat*)obj.img->clone();
}
