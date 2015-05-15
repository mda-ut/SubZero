/*
 * DataTEST.h
 *
 *  Created on: May 12, 2015
 *      Author: ahsueh1996
 */

#ifndef TEST_UTIL_DATA_DATATEST_H_
#define TEST_UTIL_DATA_DATATEST_H_

#include "../../../src/util/data/Data.h"
#include "../../../src/util/data/ImgData.h"
#include "../../../src/util/data/FPGAData.h"
#include "../../../src/util/Logger.h"
#include "../../../src/util/StringTools.h"

class DataTEST {

public:
	static int runUnits();

	/* ==========================================================================
	 * CONSTRUCTOR & DESTRUCTOR
	 * ==========================================================================
	 */

	static int T_Constructor();
	static int T_Destructor();

	/* ==========================================================================
	 * PUBLIC FUNCS COMMON TO ALL CHILDREN
	 * ==========================================================================
	 */

	static int T_getID();
	static int T_getMsg();
	static int T_setMsg();

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */

	static int T_opEqual();
	static int T_cpConstructor();

};

#endif /* TEST_UTIL_DATA_DATATEST_H_ */
