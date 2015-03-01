/*
 * FilterFactory.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: ahsueh1996
 */

#include "FilterFactory.h"

RGBFilter * FilterFactory::createRGBFilter(int r, int g, int b) {
	return new RGBFilter(r, g, b);
}
