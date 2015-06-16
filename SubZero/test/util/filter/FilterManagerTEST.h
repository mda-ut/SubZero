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
	static int runUnits();

	/* ==========================================================================
	 * CONSTRUCTOR & DESTRUCTOR
	 * ==========================================================================
	 */

	static int T_Constructor();
	static int T_Destructor();

	/* ==========================================================================
	 * MAIN FUNCTIONALITY: FILTRATION
	 * ==========================================================================
	 */

	static int T_applyFilterChain();

	/* ==========================================================================
	 * FILTER MANAGMENT FUNCTIONS: CUSTOM ID MODE and AUTO ID MODE
	 * ==========================================================================
	 */

	static int T_insertFilter();
	static int T_replaceFilter();
	static int T_deleteFilter();
	static int T_detletFilterChain();
};

#endif /* TEST_UTIL_FILTER_FILTERMANAGERTEST_H_ */
