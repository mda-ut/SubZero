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
    int runUnits();

	/* ==========================================================================
	 * CONSTRUCTOR & DESTRUCTOR
	 * ==========================================================================
	 */

    int T_Constructor();
    int T_Destructor();

	/* ==========================================================================
	 * PUBLIC FUNCS COMMON TO ALL CHILDREN
	 * ==========================================================================
	 */

    int T_getID();
    int T_getMsg();
    int T_setMsg();

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */

    int T_opEqual();
    int T_cpConstructor();

private:
    Logger* logger = new Logger("DataTEST");

};

#endif /* TEST_UTIL_DATA_DATATEST_H_ */
