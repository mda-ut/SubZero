/*
 * ImgDataTEST.cpp
 *
 *  Created on: May 16, 2015
 *      Author: ahsueh1996
 */

#include "ImgDataTEST.h"

/* TEMPLATE
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	if (fail > 0)
		Logger::warn("  TEST FAILED: _______");
	Logger::trace("==============================");
	Logger::close();
	return fail;
 */


int ImgDataTEST::runUnits() {
	int res = 0;
	Logger::trace("Running all unit tests for: ImgData");
	Logger::trace("==============================");
//	res += T_Constructor();
//	res += T_getImg();
//	res += T_getHeight();
//	res += T_getWidth();
//	res += T_cpConstructor();
//	res += T_opEqual();

	char key;
    cvNamedWindow("Camera_Output", 1);    //Create window
    CvCapture* capture = cvCaptureFromCAM(0);  //Capture using any camera connected to your system
    while(1){ //Create infinte loop for live streaming

        IplImage* frame = cvQueryFrame(capture); //Create image frames from capture
        cvShowImage("Camera_Output", frame);   //Show image frames on created window
        key = cvWaitKey(10);     //Capture Keyboard stroke

        if(char(key)==32){
        	cvSaveImage("abc.png",frame); // If you hit spacebar an image will be saved
        }

        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
    cvReleaseCapture(&capture); //Release capture.
    cvDestroyWindow("Camera_Output"); //Destroy Window
    return 0;

	Logger::trace("==============================");
	if (res != 0)
		Logger::warn(StringTools::intToStr(res)+" warning(s) in unit tests");
	Logger::trace("Unit testing complete: ImgData");
	return res;
}

/* ==========================================================================
 * CONSTRUCTOR & DESTRUCTOR
 * ==========================================================================
 */

int ImgDataTEST::T_Constructor() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	Logger::trace("Testing Constructor:");
	Logger::trace(" Init Mat obj...");
	cv::Mat* img = new cv::Mat;
	img->eye(2,2,1);
	Logger::trace(" Constructing new ImgData obj with arg \"data\" and Mat obj...");
	ImgData* data = new ImgData("data",img);
	Logger::trace(" Complete.");
	Logger::trace(" Checking initialized variables...");
	Logger::trace("  Using getID()...");
	if (data->getID() == "data")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, ID initialization incorrect");
		fail += 1;
	}
	Logger::trace("  Using getImg()...");
	if (data->getImg() != 0)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, Img initialization incorrect");
		fail += 1;
	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;
	delete img;

	if (fail > 0)
		Logger::warn("  TEST FAILED: Data Constructor");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

int ImgDataTEST::T_Destructor() {
	return 0;
}

/* ==========================================================================
 * IMG MANIPULATION FUNCS
 * ==========================================================================
 */

int ImgDataTEST::T_getImg() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	Logger::trace("Testing getImg():");
	Logger::trace(" Init Mat obj...");
	cv::Mat img = cv::Mat::eye(2,2,CV_32F);
	std::string row1,row2;
//	row1 = StringTools::intToStr(img.at(0,0)) + StringTools::intToStr(img.at(0,1));

	Logger::trace(" Constructing new ImgData obj with arg \"data\" and Mat obj...");
	ImgData* data = new ImgData("data",&img);
	Logger::trace(" Complete.");
	Logger::trace(" Obtaining copy of img using getImg()...");
//	cv::Mat* copy = data->getImg();


	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;

	if (fail > 0)
		Logger::warn("  TEST FAILED: getImg()");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

int ImgDataTEST::T_getHeight() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
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
	Logger::close();
	return fail;
}

int ImgDataTEST::T_getWidth() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
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
	Logger::close();
	return fail;
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

int ImgDataTEST::T_opEqual() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	Logger::trace("Testing operator= overload:");
	Logger::trace(" Constructing new ImgData obj with arg \"data\" and 4x5 Mat obj...");
	cv::Mat img, *imgptr;
	img = cv::Mat::eye(4,5,CV_32F);
	imgptr = &img;
	ImgData* data = new ImgData("data",imgptr);
	Logger::trace(" Set Msg to \"HII\"...");
	data->setMsg("HII");
	Logger::trace(" Assigning obj to new Data obj pointer...");
	ImgData* copy = data;
	Logger::trace(" Checking new obj variables...");
	Logger::trace("  Using getID()...");
	if (copy->getID() == "data")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, ID copy incorrect");
		fail += 1;
	}
	Logger::trace("  Using getMsg()...");
	if (data->getMsg() == "HII")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, Msg copy incorrect");
		fail += 1;
	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;

	if (fail > 0)
		Logger::warn("  TEST FAILED: operator= overload");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

int ImgDataTEST::T_cpConstructor() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	Logger::trace("Testing Copy Constructor:");
	Logger::trace(" Constructing new ImgData obj with arg \"data\" and 4x5 Mat obj...");
	cv::Mat img = cv::Mat::eye(4,5,CV_32F);
	cv::Mat* imgptr = &img;
	ImgData* data = new ImgData("data",imgptr);
	Logger::trace(" Setting Msg to \"SubZero rox\"...");
	data->setMsg("SubZero rox");
	Logger::trace(" Invoking Copy Constructor...");
	ImgData* copy = new ImgData(*data);
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
	Logger::trace("  Using getHeight() and getWidth()...");
	if (copy->getHeight() == 4 && copy->getWidth() == 5)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, Img not copied correctly");
		fail += 1;
	}

	Logger::trace(" Changing msg of copy to \"whatever\"...");
	copy->setMsg("whatever");
	Logger::trace(" Changing org img content");
	//TODO
	Logger::trace(" Checking variables...");
	Logger::trace("  Using getMsg() on original...");
	if (copy->getMsg() == "whatever")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, org Msg incorrect");
		fail += 1;
	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;
	delete copy;

	if (fail > 0)
		Logger::warn("  TEST FAILED: ImgData Copy Constructor");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}
