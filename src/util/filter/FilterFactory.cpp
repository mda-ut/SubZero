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

Filter* FilterFactory::createRGBFilter(int fullspec[]) {
	return new RGBFilter(fullspec);
}

Filter* FilterFactory::createRGBFilter(int highlight[],int midtone[],int shadow[]){
	return new RGBFilter(highlight,midtone,shadow);
}

Filter* FilterFactory::createHSVFilter(int lowH, int highH, int lowS, int highS, int lowV, int highV){
    return new HSVFilter(lowH, highH, lowS, highS, lowV, highV);
}
