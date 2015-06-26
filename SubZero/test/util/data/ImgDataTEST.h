/*
 * ImgDataTEST.h
 *
 *  Created on: May 16, 2015
 *      Author: ahsueh1996
 */

#ifndef TEST_UTIL_DATA_IMGDATATEST_H_
#define TEST_UTIL_DATA_IMGDATATEST_H_

#include "../../../src/util/data/Data.h"
#include "../../../src/util/data/ImgData.h"
#include "../../../src/util/data/FPGAData.h"
#include "../../../src/util/Logger.h"
#include "../../../src/util/StringTools.h"
#include <cv.h>
#include <highgui.h>

class ImgDataTEST {

public:
	static int runUnits();
	static cv::Mat camCap();

	/* ==========================================================================
	 * CONSTRUCTOR & DESTRUCTOR
	 * ==========================================================================
	 */

	static int T_Constructor();
	static int T_Destructor();

	/* ==========================================================================
	 * IMG MANIPULATION FUNCS
	 * ==========================================================================
	 */

	static int T_getImg();
	static int T_getHeight();
	static int T_getWidth();
	static int T_setImg();

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */

	static int T_opEqual();
	static int T_cpConstructor();


};

#endif /* TEST_UTIL_DATA_IMGDATATEST_H_ */
