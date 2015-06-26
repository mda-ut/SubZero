/*
 * RGBFilterTEST.h
 *
 *  Created on: Jun 11, 2015
 *      Author: ahsueh1996
 */

#ifndef TEST_UTIL_FILTER_RGBFILTERTEST_H_
#define TEST_UTIL_FILTER_RGBFILTERTEST_H_

#include "../../../src/util/filter/FilterManager.h"
#include "../../../src/util/filter/FilterFactory.h"
#include "../../../src/util/Logger.h"
#include "../../../src/util/StringTools.h"
#include "../data/ImgDataTEST.h"

class RGBFilterTEST {
public:
	static int runUnits();

	/* ==========================================================================
	 * CONSTRUCTOR AND DESTRUCTOR
	 * ==========================================================================
	 */
	static int T_Constructor();

	/* ==========================================================================
	 * FILTER ACTION
	 * ==========================================================================
	 */
	static int T_filter();
	static int T_setValues();

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */
	static int T_opEqual();

};

#endif /* TEST_UTIL_FILTER_RGBFILTERTEST_H_ */
