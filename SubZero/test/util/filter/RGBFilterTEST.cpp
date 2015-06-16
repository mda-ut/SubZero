/*
 * RGBFilterTEST.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: ahsueh1996
 */

#include "RGBFilterTEST.h"

/* TEMPLATE
	int fail = 0;
	Logger::trace("==============================");

	if (fail > 0)
		Logger::warn("  TEST FAILED: _______");
	Logger::trace("==============================");
	return fail;
 */

int RGBFilterTEST::runUnits() {
	int res = 0;
	Logger::trace("Running all unit tests for: RGBFilter");
	Logger::trace("==============================");
	res += T_Constructor();
	res += T_filter();
//	res += T_setValues();
//	res += T_opEqual();
	Logger::trace("==============================");
	if (res != 0)
		Logger::warn(StringTools::intToStr(res)+" warning(s) in unit tests");
	Logger::trace("Unit testing complete: RGBFilter");
	return res;
}

/* ==========================================================================
 * CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */

int RGBFilterTEST::T_Constructor() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing Constructor:");
	Logger::trace(" Init int arr[3] = {1,2,3}...");
	int arr[] = {1,2,3};
	Logger::trace(" Using filter factory, create mode 0 filter...");
	RGBFilter* rgbFilter = (RGBFilter*)FilterFactory::createRGBFilter(arr);
	Logger::trace(" Checking variables...");
	Logger::trace("  Using getValues...");
	std::vector<int> list = rgbFilter->getValues();
	std::string res;
	for (std::vector<int>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+StringTools::intToStr(*it);
	Logger::trace("   "+res);
	if (res == " 1 2 3")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, values not correct under full mode");
		fail++;
	}

	Logger::trace(" Using filter factory, create mode 1 filter...");
	rgbFilter = (RGBFilter*)FilterFactory::createRGBFilter(arr,arr,arr);
	Logger::trace(" Checking variables...");
	Logger::trace("  Using getValues...");
	list = rgbFilter->getValues();
	res = "";
	for (std::vector<int>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+StringTools::intToStr(*it);
	Logger::trace("   "+res);
	if (res == " 1 2 3 1 2 3 1 2 3")
		Logger::trace("    ok");
	else {
	Logger::warn("    NOT ok, values not correct under div mode");
		fail++;
	}

	if (fail > 0)
		Logger::warn("  TEST FAILED: Constructor");
	Logger::trace("==============================");
	return fail;
}

/* ==========================================================================
 * FILTER ACTION
 * ==========================================================================
 */

int RGBFilterTEST::T_filter() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing filter():");

//	Logger::trace(" Using imread...");
//	cv::Mat img = cv::imread("rgb_mode_0.jpg",CV_LOAD_IMAGE_COLOR);
//	if (! img.data)
//		Logger::warn(" OH NO, img not read");

	Logger::trace(" Using camCap...");
	cv::Mat img = ImgDataTEST::camCap();
	cvDestroyWindow("camCap");
	Logger::trace(" Loading test image into a ImgData wrapper...");
	ImgData* testImg = new ImgData("raw",&img);
	Logger::trace(" Copying ImgData to second wrapper...");
	ImgData* testImg2 = new ImgData(testImg);
	Logger::trace(" Showing one copy of test image (should be named \"raw\")...");
	testImg->showImg();

	Logger::trace(" Filtering first data w/ full luminosity specturm, aka mode 0...");
	Logger::trace("  Init int arr[3]...");
	int arr[] = {10,-15,-18};
	Logger::trace("  Using filter factory, create mode 0 filter...");
	RGBFilter* rgbFilter = (RGBFilter*)FilterFactory::createRGBFilter(arr);
	Logger::trace("  Creating filter manager w/ id \"RGBFilter MODE 0\"...");
	FilterManager* fm = new FilterManager("RGBFilter MODE 0");
	Logger::trace("  Inserting filter as \"rgb mode 0\"...");
	fm->insertFilter("rgb mode 0",rgbFilter);
	Logger::trace("  Attempt filtering using filter manager...");
	fm->applyFilterChain(testImg);
	Logger::trace("  Showing filtered test image...");
	testImg->showImg();
	Logger::trace("   Expect 2 windows, \"raw\" and \"RGBFilter MODE 0\", the latter should be red shifted");
	Logger::trace("   If true, hit space, else hit esc");
	char key;
	while (1) {
		key = cvWaitKey(0);
		if (char(key) == 32) {
			Logger::trace("    ok");
				break;
		}
		else if (char(key) == 27) {
			Logger::warn("    NOT ok, details of output under mode 0 not correct");
			fail++;
			break;
		}
	}

	Logger::trace(" Filtering data 2 w/ 3 zones of luminosity separately, aka mode 1...");
	Logger::trace("  Init int high[3],mid[3],shad[3]...");
	int high[] = {5,2,-1};
	int mid[] = {10,-15,-18};
	int shad[]	= {5,2,3};
	Logger::trace("  Using filter factory, create mode 1 filter...");
	rgbFilter = (RGBFilter*)FilterFactory::createRGBFilter(high,mid,shad);
	Logger::trace("  Creating filter manager w/ id \"RGBFilter MODE 1\"...");
	FilterManager* fm2 = new FilterManager("RGBFilter MODE 1");
	Logger::trace("  Inserting filter as \"rgb mode 1\"...");
	fm2->insertFilter("rgb mode 1",rgbFilter);
	Logger::trace("  Attempt filtering using filter manager...");
	fm2->applyFilterChain(testImg2);
	Logger::trace("  Showing filtered test image...");
	testImg2->showImg();
	Logger::trace("   Expect 3 windows in total, \"raw\" and \"RGBFilter MODE 0\" and \"RGBFilter MODE 1\", the latter should be red shifted, but a bit differently");
	Logger::trace("   If true, hit space, else hit esc");
	while (1) {
		key = cvWaitKey(0);
		if (char(key) == 32) {
			Logger::trace("    ok");
				break;
		}
		else if (char(key) == 27) {
			Logger::warn("    NOT ok, details of output under mode 1 not correct");
			fail++;
			break;
		}
	}

	delete fm;
	delete fm2;
	cvDestroyWindow("raw");
	testImg->closeImg();
	testImg2->closeImg();

	if (fail > 0)
		Logger::warn("  TEST FAILED: filter()");
	Logger::trace("==============================");
	return fail;
}

int RGBFilterTEST::T_setValues() {
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

int RGBFilterTEST::T_opEqual() {
}
