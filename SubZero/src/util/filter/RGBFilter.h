/*
 * RGBFilter.h
 *
 *  Created on: Feb 24, 2015
 *      Author: ahsueh1996
 */

#ifndef RGBFILTER_H_
#define RGBFILTER_H_

#include "Filter.h"

/**
 * The RGBFilter will use opencv's threshold function. It has
 * private members holding the parameter values used for this
 * opencv implementation.
 */
class RGBFilter: public Filter {

private:
	// Int variables for the rgb values used in the RGBFilter.
	int r, g, b;

public:
	/* ==========================================================================
	 * CONSTRUCTOR AND DESTRUCTOR
	 * ==========================================================================
	 */

	/**
	 * RGBFilter constructor takes in the 3 values, r, g, and b (range: 0:255),
	 * and uses them when calling the opencv's threshold function.
	 *
	 * @param r		:0-255 int values for red intensity.
	 * @param g		:0-255 int values for green intensity.
	 * @param b		:0-255 int values for blue intensity.
	 */
	RGBFilter(int r, int g, int b);

	/**
	 * Destructor
	 */
	virtual ~RGBFilter();

	/* ==========================================================================
	 * FILTER ACTION
	 * ==========================================================================
	 */

	/**
	 * Filtering function for filter obj. Takes the inputImg and filters it.
	 *
	 * @param inputImg
	 */
	int filter (ImgData* data);

	/**
	 * Set values function.
	 *
	 * @param r		:0-255 int values for red intensity.
	 * @param g		:0-255 int values for green intensity.
	 * @param b		:0-255 int values for blue intensity.
	 */
	void setValues(int r, int b, int g);

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */

	/**
	 * Operator = overload
	 *
	 * @param rhs	the filter obj on the right hand side of the = operator
	 * @return 		pointer to the new deep copy of rhs
	 */
	RGBFilter* operator=(RGBFilter* rhs);


	/**
	 * Copy constructor.
	 *
	 * @param obj	the reference of the new copy
	 */
	RGBFilter(RGBFilter* obj);

};

#endif /* RGBFILTER_H_ */
