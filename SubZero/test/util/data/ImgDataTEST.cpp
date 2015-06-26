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
	res += T_setImg();
	res += T_getHeight();
	res += T_getWidth();
	res += T_cpConstructor();

	Logger::trace("==============================");
	if (res != 0)
		Logger::warn(StringTools::intToStr(res)+" warning(s) in unit tests");
	Logger::trace("Unit testing complete: ImgData");
	Logger::trace("NOTE: all units mem tested");
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

int ImgDataTEST::T_setImg() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing setImg():");
	Logger::trace(" Creating 2 Mat obj using camCap()...");
    cv::Mat test = camCap();
    cvDestroyWindow("camCap");
    cv::Mat test2 = camCap();
    cvDestroyWindow("camCap");
    cv::namedWindow("obj 1");
    cv::imshow("obj 1",test);
    cv::namedWindow("obj 2");
    cv::imshow("obj 2",test2);
    Logger::trace("  Accessing refcount...");
    int t1rc,t2rc,imgrc;
    t1rc = test.u->refcount;
    t2rc = test2.u->refcount;
    Logger::trace("    Obj 1 refcount: "+StringTools::intToStr(t1rc));
    Logger::trace("    Obj 2 refcount: "+StringTools::intToStr(t2rc));
    if (t1rc+t2rc==2)
    	Logger::trace("    ok");
    else {
    	Logger::warn("    NOT ok, refcount should be 1 for both");
    	fail++;
    }
    Logger::trace(" Creating ImgData with obj 1...");
    ImgData* testImg = new ImgData("plswork",&test);
    Logger::trace("  Accessing refcount...");
    t1rc = test.u->refcount;
    t2rc = test2.u->refcount;
    imgrc = testImg->img->u->refcount;
    Logger::trace("    Obj 1 refcount: "+StringTools::intToStr(t1rc));
    Logger::trace("    Obj 2 refcount: "+StringTools::intToStr(t2rc));
    if (t1rc == 2) {
    	if (imgrc == 2) {
    		if(t2rc == 1)
    			Logger::trace("    ok");
    		else {
    			Logger::warn("    NOT ok, obj 2 refcount should be 1");
    			fail++;
    		}
    	}
    	else {
    		Logger::warn("    NOT ok, obj 1 refcount disagree");
    		fail++;
    	}
    } else {
    	Logger::warn("    NOT ok, obj 1 refcount should be 2");
    	fail++;
    }
    Logger::trace(" Try showImg(), expect photo to be as same as obj 1...");
    Logger::trace(" If true, hit space, else hit esc...");
    testImg->showImg();
    char key;
    while (1) {
    	key = cvWaitKey(0);
    	if (char(key) == 32) {
    		Logger::trace("    ok");
    		break;
    	}
    	else if (char(key) == 27) {
    		Logger::warn("    NOT ok, img not expected");
    		fail++;
    		break;
    	}
    }
    Logger::trace(" Setting obj 2 to img...");
    testImg->setImg(&test2);
    Logger::trace("  Accessing refcount...");
    t1rc = test.u->refcount;
    t2rc = test2.u->refcount;
    Logger::trace("    Obj 1 refcount: "+StringTools::intToStr(t1rc));
    Logger::trace("    Obj 2 refcount: "+StringTools::intToStr(t2rc));
    if (t1rc==1 && t2rc==2)
    	Logger::trace("    ok");
    else {
    	Logger::warn("    NOT ok, refcount should be 1 for obj 1 and 2 for obj 2");
    	fail++;
    }
    Logger::trace(" Release obj 2 from outside ImgData...");
    test2.release();
    Logger::trace(" Try showImg(), expect photo to be as same as obj 2...");
    testImg->showImg();
    Logger::trace(" If true, hit space, else hit esc...");
    while (1) {
    	key = cvWaitKey(0);
    	if (char(key) == 32) {
    		Logger::trace("    ok");
    		break;
    	}
    	else if (char(key) == 27) {
    		Logger::warn("    NOT ok, img not expected");
    		fail++;
    		break;
    	}
    }
    Logger::trace("  Accessing refcount...");
    t1rc = test.u->refcount;
    imgrc = testImg->img->u->refcount;
    Logger::trace("    Obj 1 refcount: "+StringTools::intToStr(t1rc));
    Logger::trace("    Obj 2 refcount: "+StringTools::intToStr(imgrc));
    if (t1rc+imgrc==2)
    	Logger::trace("    ok");
    else {
    	Logger::warn("    NOT ok, refcount should be 1 for both");
    	fail++;
    }
    Logger::trace(" Deleting ImgData...");
    delete testImg;
    Logger::trace(" Release obj 1...");
    test.release();
    cv::destroyWindow("obj 1");
    cv::destroyWindow("obj 2");

	if (fail > 0)
		Logger::warn("  TEST FAILED: setImg()");
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

//	Logger::trace(" Changing org img content...");
//	data->closeImg();
//	copy->closeImg();
//	img = ImgDataTEST::camCap();
//	cvDestroyWindow("camCap");
//	data->setImg(&img);

	Logger::trace(" Checking variables...");
	Logger::trace("  Using getMsg() on original...");
	if (copy->getMsg() == "whatever" && data->getMsg() == "SubZero rox")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, org or copy Msg incorrect");
		fail += 1;
	}
	Logger::trace(" Using refcount to check independence...");
	int datarc, copyrc;
    datarc = data->img->u->refcount;
    copyrc = copy->img->u->refcount;
	Logger::trace("    \"data\" img refcount: "+StringTools::intToStr(datarc));
	Logger::trace("    \"copy\" img refcount: "+StringTools::intToStr(copyrc));
	if (datarc==2 && copyrc ==1) {
		Logger::trace("    ok");
		fail--;
	}
	else if (datarc==3)
		Logger::warn("    NOT ok, copy's img points to data's img obj");
	else
		Logger::warn("    NOT ok, data ref should be 2, copy ref should be 1");
	fail++;
//	Logger::trace("  Showing imgs using showImg()...");
//	data->showImg("data");
//	copy->showImg("copy");
//	Logger::trace("  If copy different from data then deep copy ok press spacebar, else press esc...");
//	while (1) {
//		key = cvWaitKey(0);
//		if (char(key) == 32) {
//			Logger::trace("    ok");
//			break;
//		}
//		else if (char(key) == 27) {
//			Logger::warn("    NOT ok, img not same");
//			fail++;
//			break;
//		}
//	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;
	delete copy;

	if (fail > 0)
		Logger::warn("  TEST FAILED: ImgData Copy Constructor");
	Logger::trace("==============================");
	return fail;
}
