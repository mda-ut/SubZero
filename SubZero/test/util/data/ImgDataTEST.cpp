/*
 * ImgDataTEST.cpp
 *
 *  Created on: May 16, 2015
 *      Author: ahsueh1996
 */

#include "ImgDataTEST.h"

/* TEMPLATE
	int fail = 0;
	Logger::trace("==============================");

	if (fail > 0)
		Logger::warn("  TEST FAILED: _______");
	Logger::trace("==============================");
	return fail;
 */


int ImgDataTEST::runUnits() {
	int res = 0;
	Logger::trace("Running all unit tests for: ImgData");
	Logger::trace("==============================");

	res += T_Constructor();
	res += T_getHeight();
	res += T_getWidth();
	res += T_cpConstructor();

	Logger::trace("==============================");
	if (res != 0)
		Logger::warn(StringTools::intToStr(res)+" warning(s) in unit tests");
	Logger::trace("Unit testing complete: ImgData");
	return res;
}

cv::Mat ImgDataTEST::camCap() {
	char key;
	cv::Mat ret;
    cvNamedWindow("camCap", 1);    //Create window
    CvCapture* capture = cvCaptureFromCAM(0);  //Capture using any camera connected to your system
    while(1) { //Create infinte loop for live streaming

        IplImage* frame = cvQueryFrame(capture); //Create image frames from capture
        cvShowImage("camCap", frame);   //Show image frames on created window
        key = cvWaitKey(10);     //Capture Keyboard stroke

        if(char(key)==32 || 1==1){
        	ret = cv::cvarrToMat(frame,true,true,0); // If you hit spacebar an image will be saved
        	break;
        }

//        if (char(key) == 27){
//        	cvReleaseCapture(&capture); //Release capture.
//        	cvDestroyWindow("camCap"); //Destroy Window
//        	return cv::Mat();
//        }
    }
    cvReleaseCapture(&capture);
    return ret;
}

/* ==========================================================================
 * CONSTRUCTOR & DESTRUCTOR
 * ==========================================================================
 */

int ImgDataTEST::T_Constructor() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing Constructor:");
	Logger::trace(" Init Mat obj using camCap()...");
	Logger::trace(" Showing capped img...");
	cv::Mat img = ImgDataTEST::camCap();
	Logger::trace(" Constructing new ImgData obj with arg \"data\" and Mat obj...");
	ImgData* data = new ImgData("data",&img);
	Logger::trace(" Complete.");
	Logger::trace(" Checking initialized variables...");
	Logger::trace("  Using getID()...");
	if (data->getID() == "data")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, ID initialization incorrect");
		fail += 1;
	}
	Logger::trace("  Using showImg()...");
	Logger::trace("  If both imgs are identical press spacebar, else press esc...");
	data->showImg();
	char key;
	while (1) {
 		key = cvWaitKey(0);
		if (char(key) == 32) {
			Logger::trace("    ok");
			break;
		}
		else if (char(key) == 27) {
			Logger::warn("    NOT ok, img not same");
			fail++;
			break;
		}
	}
//	Logger::trace(" Using getImg() and comparing...");
	//TODO
	Logger::trace("Test complete.");
	Logger::trace("Closing windows...");
	data->closeImg();
	cvDestroyWindow("camCap");
	Logger::trace("Deleting data...");
	delete data;

	if (fail > 0)
		Logger::warn("  TEST FAILED: Data Constructor");
	Logger::trace("==============================");
	return fail;
}

int ImgDataTEST::T_Destructor() {
	return 0;
}

/* ==========================================================================
 * IMG MANIPULATION FUNCS
 * ==========================================================================
 */

int ImgDataTEST::T_getHeight() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing getHeight():");
	Logger::trace(" Init 10x2 Mat obj...");
	cv::Mat img = cv::Mat::eye(10,2,CV_32F);
	Logger::trace(" Creating ImgData obj...");
	ImgData* data = new ImgData("data",&img);
	Logger::trace(" Using getHeight()...");
	Logger::trace("    "+StringTools::intToStr(data->getHeight()));
	if (data->getHeight() == 10)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, height incorrect");
		fail += 1;
	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;

	if (fail > 0)
		Logger::warn("  TEST FAILED: getHeight()");
	Logger::trace("==============================");
	return fail;
}

int ImgDataTEST::T_getWidth() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing getWidth():");
	Logger::trace(" Init 10x2 Mat obj...");
	cv::Mat img = cv::Mat::eye(10,2,CV_32F);
	Logger::trace(" Creating ImgData obj...");
	ImgData* data = new ImgData("data",&img);
	Logger::trace(" Using getWidth()...");
	Logger::trace("    "+StringTools::intToStr(data->getWidth()));
	if (data->getWidth() == 2)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, width incorrect");
		fail += 1;
	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;

	if (fail > 0)
		Logger::warn("  TEST FAILED: getWidth()");
	Logger::trace("==============================");
	return fail;
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

int ImgDataTEST::T_cpConstructor() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing Copy Constructor:");
	Logger::trace(" Using camCap() to get Mat obj...");
	cv::Mat img = ImgDataTEST::camCap();
	cvDestroyWindow("camCap");
	Logger::trace(" Constructing new ImgData obj with arg \"data\" and Mat obj...");
	ImgData* data = new ImgData("data",&img);
	Logger::trace(" Setting Msg to \"SubZero rox\"...");
	data->setMsg("SubZero rox");
	Logger::trace(" Invoking Copy Constructor...");
	ImgData* copy = new ImgData(data);
	Logger::trace(" Checking variables...");
	Logger::trace("  Using getID()...");
	if (copy->getID() == "data")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, ID copy incorrect");
		fail += 1;
	}
	Logger::trace("  Using getMsg()...");
	if (copy->getMsg() == "SubZero rox")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, Msg copy incorrect");
		fail += 1;
	}
	Logger::trace("  Showing imgs using showImg()...");
	Logger::trace("  If both imgs are identical press spacebar, else press esc...");
	data->showImg("data");
	copy->showImg("copy");
	char key;
	while (1) {
		key = cvWaitKey(0);
		if (char(key) == 32) {
			Logger::trace("    ok");
			break;
		}
		else if (char(key) == 27) {
			Logger::warn("    NOT ok, img not same");
			fail++;
			break;
		}
	}

	Logger::trace(" Changing msg of copy to \"whatever\"...");
	copy->setMsg("whatever");
	Logger::trace(" Changing org img content");
	data->closeImg();
	copy->closeImg();
	img = ImgDataTEST::camCap();
	cvDestroyWindow("camCap");
	data->setImg(&img);

	Logger::trace(" Checking variables...");
	Logger::trace("  Using getMsg() on original...");
	if (copy->getMsg() == "whatever" && data->getMsg() == "SubZero rox")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, org or copy Msg incorrect");
		fail += 1;
	}
	Logger::trace("  Showing imgs using showImg()...");
	data->showImg("data");
	copy->showImg("copy");
	Logger::trace("  If copy different from data then deep copy ok press spacebar, else press esc...");
	while (1) {
		key = cvWaitKey(0);
		if (char(key) == 32) {
			Logger::trace("    ok");
			break;
		}
		else if (char(key) == 27) {
			Logger::warn("    NOT ok, img not same");
			fail++;
			break;
		}
	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;
	delete copy;

	if (fail > 0)
		Logger::warn("  TEST FAILED: ImgData Copy Constructor");
	Logger::trace("==============================");
	return fail;
}
