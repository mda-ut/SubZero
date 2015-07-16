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
#include <opencv2/highgui/highgui.hpp>

class ImgDataTEST {

public:
    int runUnits();
    cv::Mat camCap();

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

    int T_getImg();
    int T_getHeight();
    int T_getWidth();
    int T_setImg();

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */

    int T_opEqual();
    int T_cpConstructor();

private:
    Logger* logger = new Logger("ImgDataTEST");

};

#endif /* TEST_UTIL_DATA_IMGDATATEST_H_ */
