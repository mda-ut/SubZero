/*
 * RGBFilter.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: ahsueh1996
 */

#include "RGBFilter.h"


const int MXCOLOR = 255;


RGBFilter::RGBFilter(int fullspec[]) : Filter() {
	this->setValues(fullspec);
	this->setID("rgbFull");
}

RGBFilter::RGBFilter(int highlight[], int midtone[], int shadow[]) : Filter() {
	this->setValues(highlight,midtone,shadow);
	this->setID("rgbDiv");
}

RGBFilter::~RGBFilter() {
	// TODO Auto-generated destructor stub
}


int RGBFilter::filter(Data* data) {
	// check for whether the input is of the correct type.
	ImgData* cast = dynamic_cast<ImgData*>(data);
	if (cast == 0) {
		// track the error and return error
		this->track(data,this->filterID,1,1);
		return 1;
	}

	// begin filter sequence.
	int newPixelVal;
	cv::Mat filteredImg = (cast->getImg())->clone();
	cv::Mat BGR[3];

	cv::split(filteredImg,BGR);
	// catch error?

	// Full spectrum mode

	if(this->mode == 0) {
		for(int y = 0; y < (cast->getImg())->cols; y++ ) {
			for(int x = 0; x < (cast->getImg())->rows; x++ ) {
				for(int c = 0; c < 3; c++) {
					newPixelVal = BGR[c].at<char>(x,y) + midtone[c];
					if(newPixelVal < 0)
						newPixelVal = 0;
					else if (newPixelVal > MXCOLOR)
						newPixelVal = MXCOLOR;
					BGR[c].at<char>(x,y) = newPixelVal;
				}
			}
		}
	}

	// 3 zone mode
	if (this->mode == 1) {
		int luminosity;
		const int SHADTHRESHOLD = (int) MXCOLOR*10/3;
		const int HIGHTHRESHOLD = SHADTHRESHOLD * 2;
		// get luminosity with some function
		// use luminosity as a switch for case using high, mid or shad
		for(int y = 0; y < (cast->getImg())->cols; y++ ) {
			for(int x = 0; x < (cast->getImg())->rows; x++ ) {
				// From 11%,59%,30% bgr respectively. Scaled to 1:6:3 factors
				// luminosity range is from 0-2550, 1/3 is 850. Calc this from:
				// 10*255, 10* MXCOLOR
				luminosity = BGR[0].at<char>(x,y)*1+BGR[1].at<char>(x,y)*6+BGR[2].at<char>(x,y)*3;

				for(int c = 0; c < 3; c++) {

					if (luminosity < SHADTHRESHOLD)
						newPixelVal = BGR[c].at<char>(x,y) + shadow[c];
					else if (luminosity > HIGHTHRESHOLD)
						newPixelVal = BGR[c].at<char>(x,y) + highlight[c];
					else
						newPixelVal = BGR[c].at<char>(x,y) + midtone[c];

					if(newPixelVal < 0)
						newPixelVal = 0;
					else if (newPixelVal > MXCOLOR)
						newPixelVal = MXCOLOR;
					BGR[c].at<char>(x,y) = newPixelVal;
				}
			}
		}
	}

	//joining seq
	cv::merge(BGR,3,filteredImg);

	//set sequence
	cast->setImg(&filteredImg);

	// end sequence.

	// track and return
	this->track(cast,this->filterID,0,0);
	return 0;
}

void RGBFilter::setValues(int fullspec[]){
	this->mode = 0;
	this->midtone[0] = fullspec[2];
	this->midtone[1] = fullspec[1];
	this->midtone[2] = fullspec[0];
}

void RGBFilter::setValues(int highlight[], int midtone[], int shadow[]) {
	this->mode = 1;
	this->highlight[0] = highlight[2];
	this->highlight[1] = highlight[1];
	this->highlight[2] = highlight[0];
	this->midtone[0] = midtone[2];
	this->midtone[1] = midtone[1];
	this->midtone[2] = midtone[0];
	this->shadow[0] = shadow[2];
	this->shadow[1] = shadow[1];
	this->shadow[2] = shadow[0];
}

std::vector<int> RGBFilter::getValues() {
	std::vector<int> ret;
	if (mode == 0) {
		ret.push_back(this->midtone[2]);
		ret.push_back(this->midtone[1]);
		ret.push_back(this->midtone[0]);
	} else if (mode == 1) {
		ret.push_back(this->highlight[2]);
		ret.push_back(this->highlight[1]);
		ret.push_back(this->highlight[0]);
		ret.push_back(this->midtone[2]);
		ret.push_back(this->midtone[1]);
		ret.push_back(this->midtone[0]);
		ret.push_back(this->shadow[2]);
		ret.push_back(this->shadow[1]);
		ret.push_back(this->shadow[0]);
	}
	return ret;
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

RGBFilter* RGBFilter::operator =(RGBFilter* rhs) {
	return new RGBFilter(rhs);
}


RGBFilter::RGBFilter(RGBFilter* obj) : Filter(obj) {
	this->mode = obj->mode;
	this->highlight[0] = obj->highlight[0];
	this->highlight[1] = obj->highlight[1];
	this->highlight[2] = obj->highlight[2];
	this->midtone[0] = obj->midtone[0];
	this->midtone[1] = obj->midtone[1];
	this->midtone[2] = obj->midtone[2];
	this->shadow[0] = obj->shadow[0];
	this->shadow[1] = obj->shadow[1];
	this->shadow[2] = obj->shadow[2];
}


