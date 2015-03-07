/*
 * FilterFactory.h
 *
 *  Created on: Feb 28, 2015
 *      Author: ahsueh1996
 */

#ifndef FILTERFACTORY_H_
#define FILTERFACTORY_H_
#include "RGBFilter.h"


class FilterFactory {
	/*
	 * This class holds static functions that can create all the filters
	 * defined by the project. Generally, each function will then return
	 * a pointer to the filter it created. In this class, NEW is used.
	 */
public:

	// RGB filter is created.
	static RGBFilter * createRGBFilter(std::string ID, int r, int g, int b);
};

#endif /* FILTERFACTORY_H_ */
