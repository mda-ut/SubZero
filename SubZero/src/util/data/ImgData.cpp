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

ImgData::ImgData(std::string dataID,cv::Mat* img) : Data(dataID) {
	this->img = img;
}

ImgData::~ImgData() {
	this->closeImg();
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
	return this->img->rows;
}

int ImgData::getWidth() {
	return this->img->cols;
}

void ImgData::showImg(std::string windowName) {
	if (this->img != 0) {
		try {
			if (windowName != "") {
				cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);
				cv::imshow(windowName,*this->img);
				this->windowName = windowName;
			} else {
				cv::namedWindow(this->dataID, CV_WINDOW_AUTOSIZE);    //Create window
				cv::imshow(this->dataID,*this->img);   //Show image frames on created window
			}
		} catch (cv::Exception) {
			Logger::warn("Unable to show \""+this->dataID+"\"'s img, cv::exception");
		}
	}
}

void ImgData::closeImg() {
	cv::namedWindow(this->dataID);
	cv::namedWindow(windowName);
	cv::destroyWindow(windowName);
	cv::destroyWindow(this->dataID); //Destroy Window
}

//int ImgData::compareImg(cv::Mat* testImg, cv::Mat* mask) {
//	if (testImg == 0 || this->img == 0)
//		return -1;
//	cv::compare(this->img,testImg,mask,0);
//
//}


/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

ImgData* ImgData::operator =(ImgData* rhs) {
	return new ImgData(rhs);
}

ImgData::ImgData(const ImgData* obj) : Data(obj) {
	cv::Mat *copy = new cv::Mat(obj->img->clone());
	this->img = copy;
}

