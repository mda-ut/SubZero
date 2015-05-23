/*
 * RGBFilter.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: ahsueh1996
 */

#include "RGBFilter.h"

RGBFilter::RGBFilter(int r, int g, int b) : Filter() {
	this->setValues(r,g,b);
	this->setID("rgb");
}

RGBFilter::~RGBFilter() {
	// TODO Auto-generated destructor stub
}
//
//int RGBFilter::filter (ImgData* camData) {
//	camData->procImg.push(threshold(blahbe, camData->rawImg));
//	return 0;
//}
//
//
void RGBFilter::setValues(int r, int g, int b){
	this -> r = r;
	this -> g = g;
	this -> b = b;
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

RGBFilter* RGBFilter::operator =(RGBFilter* rhs) {
	return new RGBFilter(rhs);
}

RGBFilter::RGBFilter(RGBFilter* obj) : Filter(obj) {
	this->b = obj->b;
	this->g = obj->g;
	this->r = obj->r;
}
