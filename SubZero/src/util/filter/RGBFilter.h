/*
 * RGBFilter.h
 *
 *  Created on: Feb 24, 2015
 *      Author: ahsueh1996
 */

#ifndef RGBFILTER_H_
#define RGBFILTER_H_

#include "Filter.h"
#include "../PropertyReader.h"
#include <vector>
#include <math.h>

/**
 * The RBGFilter allows user to raise and lower pixel value of
 * each channel (R,B,G). The filter can be set to divide the img
 * to highlight, midtone, and shadow zone(of the luminosity histogram)
 * when correcting the color balance.
 *
 * Uses opencv's: split, join,
 */
class RGBFilter: public Filter {

private:
	/*
	 * Int variables for the rgb values used in the RGBFilter.
	 * The value x implies the operation: pixel val + x.
	 * So if x is -5 this implies: pixel val + -5.
	 */
	unsigned char highlight [3];
	unsigned char midtone [3];
	unsigned char shadow [3];

	/*
	 * Int 1 or -1 multiplier to carry the sign of the int arg.
	 */
	int highMult[3];
	int midMult[3];
	int shadMult[3];

	/*
	 * 0 for no divide, 1 for dividing into 3 zones.
	 */
	int mode;

    /*
     * "constant" max rgb color value.
     */
    int mxColour;

public:
	/* ==========================================================================
	 * CONSTRUCTOR AND DESTRUCTOR
	 * ==========================================================================
	 */

	/**
	 * RGBFilter constructor takes in the 3 values, r, g, and b
	 * and uses them across the whole img.
	 *
	 * @param fullspec		:int arr[3] for rgb offset in the full spectrum.
	 */
	RGBFilter(int fullspec []);

	/**
	 * RGBFilter constructor takes in the 3 values, r, g, and b
	 * and uses them across the whole img.
	 *
	 * @param highlight		:int arr[3] values for rgb offset in the highlight region.
	 * @param midtone		:int arr[3] values for rgb offset in the midtone region.
	 * @param shadow		:int arr[3] values for rgb offset in the shadow region.
	 */
	RGBFilter(int highlight [], int midtone [], int shadow[]);

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
	 * @return	0 for success, 1 for incorret arg, 2 for incorrect Mat type.
	 */
    bool filter (Data* data);

	/**
	 * Set values and mode.
	 *
	 * @param fullspec		:int values for rgb offset in the full spectrum.
	 */
	void setValues(int fullspec[]);

	/**
	 * Set values and mode.
	 *
	 * @param highlight		:int arr values for rgb offset in the highlight region.
	 * @param midtone		:int arr values for rgb offset in the midtone region.
	 * @param shadow		:int arr values for rgb offset in the shadow region.
	 */
	void setValues(int highlight[], int midtone[], int shadow[]);

	/**
	 * Returns values applicable to the current mode.
	 *
	 * @return		int values stored in r,g,b format for Full mode and r,g,b(highlight),r,g,b(mid),r,g,b(shadow) for div mode.
	 */
	std::vector<int> getValues();

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
    //RGBFilter* operator=(RGBFilter* rhs);


	/**
	 * Copy constructor.
	 *
	 * @param obj	the reference of the new copy
	 */
    //RGBFilter(RGBFilter* obj);

};

#endif /* RGBFILTER_H_ */
