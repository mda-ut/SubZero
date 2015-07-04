/*
 * RGBFilterTEST.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: ahsueh1996
 */

#include "RGBFilterTEST.h"

/* TEMPLATE
	int fail = 0;
    logger->trace("==============================");

	if (fail > 0)
        logger->warn("  TEST FAILED: _______");
    logger->trace("==============================");
	return fail;
 */

int RGBFilterTEST::runUnits() {
	int res = 0;
    logger->trace("Running all unit tests for: RGBFilter");
    logger->trace("==============================");
        res += T_Constructor(); //uncomment this line to replicate crash
	res += T_filter();
    logger->trace("==============================");
	if (res != 0)
        logger->warn(StringTools::intToStr(res)+" warning(s) in unit tests");
    logger->trace("Unit testing complete: RGBFilter");
	return res;
}

/* ==========================================================================
 * CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */

int RGBFilterTEST::T_Constructor() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing Constructor:");
    logger->trace(" Init int arr[3] = {1,2,3}...");
	int arr[] = {1,2,3};
    logger->trace(" Using filter factory, create mode 0 filter...");
        RGBFilter* rgbFilter = (RGBFilter*)FilterFactory::createRGBFilter(arr); //this line causes the crash: malloc:mem corruption
    logger->trace(" Checking variables...");
    logger->trace("  Using getValues...");
	std::vector<int> list = rgbFilter->getValues();
	std::string res;
	for (std::vector<int>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+StringTools::intToStr(*it);
    logger->trace("   "+res);
	if (res == " 1 2 3")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, values not correct under full mode");
		fail++;
	}
        delete rgbFilter;
    logger->trace(" Using filter factory, create mode 1 filter...");
	rgbFilter = (RGBFilter*)FilterFactory::createRGBFilter(arr,arr,arr);
    logger->trace(" Checking variables...");
    logger->trace("  Using getValues...");
	list = rgbFilter->getValues();
	res = "";
	for (std::vector<int>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+StringTools::intToStr(*it);
    logger->trace("   "+res);
	if (res == " 1 2 3 1 2 3 1 2 3")
        logger->trace("    ok");
	else {
    logger->warn("    NOT ok, values not correct under div mode");
		fail++;
	}
	delete rgbFilter;

	if (fail > 0)
        logger->warn("  TEST FAILED: Constructor");
    logger->trace("==============================");
	return fail;
}

/* ==========================================================================
 * FILTER ACTION
 * ==========================================================================
 */

int RGBFilterTEST::T_filter() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing filter():");

//	logger->trace(" Using imread...");
//	cv::Mat img = cv::imread("rgb_mode_0.jpg",CV_LOAD_IMAGE_COLOR);
//	if (! img.data)
//		logger->warn(" OH NO, img not read");

    logger->trace(" Using camCap...");
    ImgDataTEST* imgTest = new ImgDataTEST();
    cv::Mat img = imgTest->camCap();
	cvDestroyWindow("camCap");
    logger->trace(" Loading test image into a ImgData wrapper...");
    ImgData* testImg = new ImgData("raw",img);
    logger->trace(" Copying ImgData to second wrapper...");
    ImgData* testImg2 = new ImgData(*testImg);
    logger->trace(" Showing one copy of test image (should be named \"raw\")...");
	testImg->showImg();

    logger->trace(" Filtering first data w/ full luminosity specturm, aka mode 0...");
    logger->trace("  Init int arr[3]...");
	int arr[] = {25,-15,-20};
    logger->trace("  Using filter factory, create mode 0 filter...");
	RGBFilter* rgbFilter = new RGBFilter(arr);//(RGBFilter*)FilterFactory::createRGBFilter(arr);
    logger->trace("  Creating filter manager w/ id \"RGBFilter MODE 0\"...");
	FilterManager* fm = new FilterManager("RGBFilter MODE 0");
    logger->trace("  Inserting filter as \"rgb mode 0\"...");
	fm->insertFilter("rgb mode 0",rgbFilter);
    logger->trace("  Attempt filtering using filter manager...");
	fm->applyFilterChain(testImg);
    logger->trace("  Showing filtered test image...");
	testImg->showImg();
    logger->trace("   Expect 2 windows, \"raw\" and \"RGBFilter MODE 0\", the latter should be red shifted");
    logger->trace("   If true, hit space, else hit esc");
	char key;
	while (1) {
		key = cvWaitKey(0);
		if (char(key) == 32) {
            logger->trace("    ok");
				break;
		}
		else if (char(key) == 27) {
            logger->warn("    NOT ok, details of output under mode 0 not correct");
			fail++;
			break;
		}
	}

    logger->trace(" Filtering data 2 w/ 3 zones of luminosity separately, aka mode 1...");
    logger->trace("  Init int high[3],mid[3],shad[3]...");
	int high[] = {255,255,255};
	int mid[] = {50,-30,-30};
	int shad[]	= {-255,-255,-255};
    logger->trace("  Using filter factory, create mode 1 filter...");
	RGBFilter* rgbFilter2 = new RGBFilter(high,mid,shad);//(RGBFilter*)FilterFactory::createRGBFilter(high,mid,shad);
    logger->trace("  Creating filter manager w/ id \"RGBFilter MODE 1\"...");
	FilterManager* fm2 = new FilterManager("RGBFilter MODE 1");
    logger->trace("  Inserting filter as \"rgb mode 1\"...");
	fm2->insertFilter("rgb mode 1",rgbFilter2);
    logger->trace("  Attempt filtering using filter manager...");
	fm2->applyFilterChain(testImg2);
    logger->trace("  Showing filtered test image...");
	testImg2->showImg();
    logger->trace("   Expect 3 windows in total, \"raw\" and \"RGBFilter MODE 0\" and \"RGBFilter MODE 1\", the latter should be red shifted, but a bit differently");
    logger->trace("   If true, hit space, else hit esc");
	while (1) {
		key = cvWaitKey(0);
		if (char(key) == 32) {
            logger->trace("    ok");
				break;
		}
		else if (char(key) == 27) {
            logger->warn("    NOT ok, details of output under mode 1 not correct");
			fail++;
			break;
		}
	}

	delete fm;
	delete fm2;
	cvDestroyWindow("raw");
	testImg->closeImg();
	testImg2->closeImg();
    delete testImg;
    delete testImg2;
    img.release();

	if (fail > 0)
        logger->warn("  TEST FAILED: filter()");
    logger->trace("==============================");
	return fail;
}

int RGBFilterTEST::T_setValues() {
    return 0;
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

int RGBFilterTEST::T_opEqual() {
	return 0;
}
