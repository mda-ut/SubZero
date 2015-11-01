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
    int runUnits();

	/* ==========================================================================
	 * CONSTRUCTOR AND DESTRUCTOR
	 * ==========================================================================
	 */
    int T_Constructor();

	/* ==========================================================================
	 * FILTER ACTION
	 * ==========================================================================
	 */
    int T_filter();
    int T_setValues();

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */
    int T_opEqual();

private:
    Logger* logger = new Logger("RGBFiterTEST");

};

#endif /* TEST_UTIL_FILTER_RGBFILTERTEST_H_ */
