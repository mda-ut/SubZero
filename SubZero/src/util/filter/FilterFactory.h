/*
 * FilterFactory.h
 *
 *  Created on: Feb 28, 2015
 *      Author: ahsueh1996
 */

#ifndef FILTERFACTORY_H_
#define FILTERFACTORY_H_
#include "Filter.h"
#include "NullImgFilter.h"
#include "NullFPGAFilter.h"
#include "RGBFilter.h"
#include "HSVFilter.h"

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
	 * General filter is created.
	 */
	static Filter* createFilter();

	/**
	 * Null filter that takes Img as filter() arg
	 */
	static Filter* createNullImgFilter();

	/**
	 * Null filter that takes FPGA as filter() arg
	 */
	static Filter* createNullFPGAFilter();

	/**
	 * RGB filter is created.
	 *
	 * @param fullspec		:int arrary of size 3 for rgb offset in the full spectrum.
	 * @return 		filter object pointer
	 */
	static Filter* createRGBFilter(int fullspec[]);

	/**
	 * RGB filter is created.
	 *
	 * @param highlight		:int arr[3] values for rgb offset in the highlight region.
	 * @param midtone		:int arr[3] values for rgb offset in the midtone region.
	 * @param shadow		:int arr[3] values for rgb offset in the shadow region.
	 * @return 		filter object pointer
	 */
	static Filter* createRGBFilter(int highlight[],int midtone[],int shadow[]);

    static Filter* createHSVFilter(int lowH, int highH, int lowS, int highS, int lowV, int highhV);
};

#endif /* FILTERFACTORY_H_ */
