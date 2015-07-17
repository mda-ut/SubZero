/*
 * FPGADataTEST.h
 *
 *  Created on: Jun 3, 2015
 *      Author: ahsueh1996
 */

#ifndef TEST_UTIL_DATA_FPGADATATEST_H_
#define TEST_UTIL_DATA_FPGADATATEST_H_

#include "../../../src/util/data/Data.h"
#include "../../../src/util/data/ImgData.h"
#include "../../../src/util/data/FPGAData.h"
#include "../../../src/util/Logger.h"
#include "../../../src/util/StringTools.h"
//#include <linux/module.h>
//#include <linux/kernel.h>
//#include <linux/usb.h>


class FPGADataTEST {

public:
    int runUnits();

	/* ==========================================================================
	 * CONSTRUCTOR & DESTRUCTOR
	 * ==========================================================================
	 */

    int T_Constructor();
    int T_Destructor();

	/* ==========================================================================
	 * IMG MANIPULATION FUNCS
	 * ==========================================================================
	 */

	//	tested in constructor

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */

    int T_opEqual();
    int T_cpConstructor();

private:
    Logger* logger = new Logger("FPGADataTEST");

};

#endif /* TEST_UTIL_DATA_FPGADATATEST_H_ */
