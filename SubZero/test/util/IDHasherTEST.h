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

	static int runUnits();

	/* ==========================================================================
	 * CONSTRUCTOR AND DESTRUCTOR
	 * ==========================================================================
	 */

	static int T_Constructor();
	static int T_Destructor();

	/* ==========================================================================
	 * BASIC ADT METHODS
	 * ==========================================================================
	 */

	static int T_get();
	static int T_insByIndex();
	static int T_insByID();
	static int T_delByIndex();
	static int T_delByID();
	static int T_delAll();

	/* ===========================================================================
	 * SUPPLAMENTS
	 * ===========================================================================
	 */
	static int T_getNodeIDList();
};

#endif /* TEST_UTIL_IDHASHERTEST_H_ */
