/*
 * RGBFilter.h
 *
 *  Created on: Feb 24, 2015
 *      Author: ahsueh1996
 */

#ifndef RGBFILTER_H_
#define RGBFILTER_H_
#include "Filter.h"

class RGBFilter: public Filter {
	/*
	 * The RGBFilter will use opencv's threshold function. It has
	 * private members holding the parameter values used for this
	 * opencv implementation.
	 */
public:
	RGBFilter(int r, int g, int b);
	virtual ~RGBFilter();

	// Filter function for filter
	int filter (ImgData * inputImg);

	// Set values function.
	void setValues(int r, int b, int g);

private:
	// Int variables for the rgb values used in the RGBFilter.
	int r, g, b;
};

#endif /* RGBFILTER_H_ */
