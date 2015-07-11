/*
 * IDHasherTEST.h
 *
 *  Created on: May 8, 2015
 *      Author: ahsueh1996
 */

#ifndef TEST_UTIL_IDHASHERTEST_H_
#define TEST_UTIL_IDHASHERTEST_H_

#include "../../src/util/IDHasher.h"
#include "../../src/util/Logger.h"
#include "../../src/util/StringTools.h"


class IDHasherTEST {
public:

    int runUnits();

	/* ==========================================================================
	 * CONSTRUCTOR AND DESTRUCTOR
	 * ==========================================================================
	 */

    int T_Constructor();
    int T_Destructor();

	/* ==========================================================================
	 * BASIC ADT METHODS
	 * ==========================================================================
	 */

    int T_get();
    int T_insByIndex();
    int T_insByID();
    int T_delByIndex();
    int T_delByID();
    int T_delAll();

	/* ===========================================================================
	 * SUPPLAMENTS
	 * ===========================================================================
	 */
    int T_getNodeIDList();

private:
    Logger* logger = new Logger("IDHasherTEST");
};

#endif /* TEST_UTIL_IDHASHERTEST_H_ */
