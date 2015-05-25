/*
 * FilterFactory.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: ahsueh1996
 */

#include "FilterFactory.h"

Filter* FilterFactory::createFilter() {
	return new Filter();
}

Filter* FilterFactory::createNullImgFilter() {
	return new NullImgFilter();
}

Filter* FilterFactory::createNullFPGAFilter() {
	return new NullFPGAFilter();
}

Filter* FilterFactory::createRGBFilter(int r, int g, int b) {
	return new RGBFilter(r,g,b);
}


