/*
 * FilterFactory.h
 *
 *  Created on: Feb 28, 2015
 *      Author: ahsueh1996
 */

#ifndef FILTERFACTORY_H_
#define FILTERFACTORY_H_
#include "Filter.h"

/**
 * This class holds static functions that can create all the filters
 * defined by the project. Generally, each function will then return
 * a pointer to the filter it created. In this class, NEW is used.
 */
class FilterFactory {

public:
	/* ==========================================================================
	 * STATIC CREATORS OF FILTER OBJECTS
	 * All creators return Filter* type cast for generality
	 * ==========================================================================
	 */

	/**
	 * RGB filter is created.
	 *
	 * @param r		:0-255 int values for red intensity.
	 * @param g		:0-255 int values for green intensity.
	 * @param b		:0-255 int values for blue intensity.
	 * @return filter object pointer
	 */
	static Filter* createRGBFilter(int r, int g, int b);
};

#endif /* FILTERFACTORY_H_ */
