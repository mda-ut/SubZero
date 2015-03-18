/*
 * RGBFilter.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: ahsueh1996
 */

#include "RGBFilter.h"

RGBFilter::RGBFilter(int r, int g, int b) {
	setValues(r,g,b);
}

RGBFilter::~RGBFilter() {
	// TODO Auto-generated destructor stub
}

int RGBFilter::filter (CamData* camData) {
	camData->procImg.push(threshold(blahbe, camData->rawImg));
	return 0;
}


void RGBFilter::setValues(int r, int g, int b){
	this -> r = r;
	this -> g = g;
	this -> b = b;
}
