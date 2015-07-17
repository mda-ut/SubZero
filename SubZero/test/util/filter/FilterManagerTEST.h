/*
 * FilterManagerTEST.h
 *
 *  Created on: May 19, 2015
 *      Author: ahsueh1996
 */

#ifndef TEST_UTIL_FILTER_FILTERMANAGERTEST_H_
#define TEST_UTIL_FILTER_FILTERMANAGERTEST_H_

#include "../../../src/util/filter/FilterManager.h"
#include "../../../src/util/filter/FilterFactory.h"
#include "../../../src/util/Logger.h"
#include "../../../src/util/StringTools.h"


class FilterManagerTEST {

public:
    int runUnits();

	/* ==========================================================================
	 * CONSTRUCTOR & DESTRUCTOR
	 * ==========================================================================
	 */

    int T_Constructor();
    int T_Destructor();

	/* ==========================================================================
	 * MAIN FUNCTIONALITY: FILTRATION
	 * ==========================================================================
	 */

    int T_applyFilterChain();

	/* ==========================================================================
	 * FILTER MANAGMENT FUNCTIONS: CUSTOM ID MODE and AUTO ID MODE
	 * ==========================================================================
	 */

    int T_insertFilter();
    int T_replaceFilter();
    int T_deleteFilter();
    int T_detletFilterChain();

private:
    Logger* logger = new Logger("FilterManagerTEST");

};

#endif /* TEST_UTIL_FILTER_FILTERMANAGERTEST_H_ */
