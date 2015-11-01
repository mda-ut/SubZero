/*
 * ImgDataTEST.cpp
 *
 *  Created on: May 16, 2015
 *      Author: ahsueh1996
 */

#include "ImgDataTEST.h"

/* TEMPLATE
	int fail = 0;
    logger->trace("==============================");

	if (fail > 0)
        logger->warn("  TEST FAILED: _______");
    logger->trace("==============================");
	return fail;
 */


int ImgDataTEST::runUnits() {
	int res = 0;
    logger->trace("Running all unit tests for: ImgData");
    logger->trace("==============================");

	res += T_Constructor();
	res += T_setImg();
	res += T_getHeight();
	res += T_getWidth();
	res += T_cpConstructor();

    logger->trace("==============================");
	if (res != 0)
        logger->warn(StringTools::intToStr(res)+" warning(s) in unit tests");
    logger->trace("Unit testing complete: ImgData");
    logger->trace("NOTE: all units mem tested");
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
    logger->trace("==============================");

    logger->trace("Testing Constructor:");
    logger->trace(" Init Mat obj using camCap()...");
    logger->trace(" Showing capped img...");
	cv::Mat img = ImgDataTEST::camCap();
    logger->trace(" Constructing new ImgData obj with arg \"data\" and Mat obj...");
    ImgData* data = new ImgData("data", img);
    logger->trace(" Complete.");
    logger->trace(" Checking initialized variables...");
    logger->trace("  Using getID()...");
	if (data->getID() == "data")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, ID initialization incorrect");
		fail += 1;
	}
    logger->trace("  Using showImg()...");
    logger->trace("  If both imgs are identical press spacebar, else press esc...");
	data->showImg();
	char key;
	while (1) {
 		key = cvWaitKey(0);
		if (char(key) == 32) {
            logger->trace("    ok");
			break;
		}
		else if (char(key) == 27) {
            logger->warn("    NOT ok, img not same");
			fail++;
			break;
		}
	}
//	logger->trace(" Using getImg() and comparing...");
	//TODO
    logger->trace("Test complete.");
    logger->trace("Closing windows...");
	data->closeImg();
	cvDestroyWindow("camCap");
    logger->trace("Deleting data...");
	delete data;

	if (fail > 0)
        logger->warn("  TEST FAILED: Data Constructor");
    logger->trace("==============================");
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
    logger->trace("==============================");

    logger->trace("Testing getHeight():");
    logger->trace(" Init 10x2 Mat obj...");
	cv::Mat img = cv::Mat::eye(10,2,CV_32F);
    logger->trace(" Creating ImgData obj...");
    ImgData* data = new ImgData("data", img);
    logger->trace(" Using getHeight()...");
    logger->trace("    "+StringTools::intToStr(data->getHeight()));
	if (data->getHeight() == 10)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, height incorrect");
		fail += 1;
	}
    logger->trace("Test complete.");
    logger->trace("Deleting data...");
	delete data;

	if (fail > 0)
        logger->warn("  TEST FAILED: getHeight()");
    logger->trace("==============================");
	return fail;
}

int ImgDataTEST::T_getWidth() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing getWidth():");
    logger->trace(" Init 10x2 Mat obj...");
	cv::Mat img = cv::Mat::eye(10,2,CV_32F);
    logger->trace(" Creating ImgData obj...");
    ImgData* data = new ImgData("data",img);
    logger->trace(" Using getWidth()...");
    logger->trace("    "+StringTools::intToStr(data->getWidth()));
	if (data->getWidth() == 2)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, width incorrect");
		fail += 1;
	}
    logger->trace("Test complete.");
    logger->trace("Deleting data...");
	delete data;

	if (fail > 0)
        logger->warn("  TEST FAILED: getWidth()");
    logger->trace("==============================");
	return fail;
}

int ImgDataTEST::T_setImg() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing setImg():");
    logger->trace(" Creating 2 Mat obj using camCap()...");
    cv::Mat test = camCap();
    cvDestroyWindow("camCap");
    cv::Mat test2 = camCap();
    cvDestroyWindow("camCap");
    cv::namedWindow("obj 1");
    cv::imshow("obj 1",test);
    cv::namedWindow("obj 2");
    cv::imshow("obj 2",test2);
    logger->trace("  Accessing refcount...");
    int t1rc,t2rc,imgrc;
    t1rc = test.u->refcount;
    t2rc = test2.u->refcount;
    logger->trace("    Obj 1 refcount: "+StringTools::intToStr(t1rc));
    logger->trace("    Obj 2 refcount: "+StringTools::intToStr(t2rc));
    if (t1rc+t2rc==2)
        logger->trace("    ok");
    else {
        logger->warn("    NOT ok, refcount should be 1 for both");
    	fail++;
    }
    logger->trace(" Creating ImgData with obj 1...");
    ImgData* testImg = new ImgData("plswork", test);
    logger->trace("  Accessing refcount...");
    t1rc = test.u->refcount;
    t2rc = test2.u->refcount;
    imgrc = testImg->img.u->refcount;
    logger->trace("    Obj 1 refcount: "+StringTools::intToStr(t1rc));
    logger->trace("    Obj 2 refcount: "+StringTools::intToStr(t2rc));
    if (t1rc == 2) {
    	if (imgrc == 2) {
    		if(t2rc == 1)
                logger->trace("    ok");
    		else {
                logger->warn("    NOT ok, obj 2 refcount should be 1");
    			fail++;
    		}
    	}
    	else {
            logger->warn("    NOT ok, obj 1 refcount disagree");
    		fail++;
    	}
    } else {
        logger->warn("    NOT ok, obj 1 refcount should be 2");
    	fail++;
    }
    logger->trace(" Try showImg(), expect photo to be as same as obj 1...");
    logger->trace(" If true, hit space, else hit esc...");
    testImg->showImg();
    char key;
    while (1) {
    	key = cvWaitKey(0);
    	if (char(key) == 32) {
            logger->trace("    ok");
    		break;
    	}
    	else if (char(key) == 27) {
            logger->warn("    NOT ok, img not expected");
    		fail++;
    		break;
    	}
    }
    logger->trace(" Setting obj 2 to img...");
    testImg->setImg(test2);
    logger->trace("  Accessing refcount...");
    t1rc = test.u->refcount;
    t2rc = test2.u->refcount;
    logger->trace("    Obj 1 refcount: "+StringTools::intToStr(t1rc));
    logger->trace("    Obj 2 refcount: "+StringTools::intToStr(t2rc));
    if (t1rc==1 && t2rc==2)
        logger->trace("    ok");
    else {
        logger->warn("    NOT ok, refcount should be 1 for obj 1 and 2 for obj 2");
    	fail++;
    }
    logger->trace(" Release obj 2 from outside ImgData...");
    test2.release();
    logger->trace(" Try showImg(), expect photo to be as same as obj 2...");
    testImg->showImg();
    logger->trace(" If true, hit space, else hit esc...");
    while (1) {
    	key = cvWaitKey(0);
    	if (char(key) == 32) {
            logger->trace("    ok");
    		break;
    	}
    	else if (char(key) == 27) {
            logger->warn("    NOT ok, img not expected");
    		fail++;
    		break;
    	}
    }
    logger->trace("  Accessing refcount...");
    t1rc = test.u->refcount;
    imgrc = testImg->img.u->refcount;
    logger->trace("    Obj 1 refcount: "+StringTools::intToStr(t1rc));
    logger->trace("    Obj 2 refcount: "+StringTools::intToStr(imgrc));
    if (t1rc+imgrc==2)
        logger->trace("    ok");
    else {
        logger->warn("    NOT ok, refcount should be 1 for both");
    	fail++;
    }
    logger->trace(" Deleting ImgData...");
    delete testImg;
    logger->trace(" Release obj 1...");
    test.release();
    cv::destroyWindow("obj 1");
    cv::destroyWindow("obj 2");

	if (fail > 0)
        logger->warn("  TEST FAILED: setImg()");
    logger->trace("==============================");
	return fail;
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

int ImgDataTEST::T_cpConstructor() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing Copy Constructor:");
    logger->trace(" Using camCap() to get Mat obj...");
	cv::Mat img = ImgDataTEST::camCap();
	cvDestroyWindow("camCap");
    logger->trace(" Constructing new ImgData obj with arg \"data\" and Mat obj...");
    ImgData* data = new ImgData("data",img);
    logger->trace(" Setting Msg to \"SubZero rox\"...");
	data->setMsg("SubZero rox");
    logger->trace(" Invoking Copy Constructor...");
    ImgData* copy = new ImgData(*data);
    logger->trace(" Checking variables...");
    logger->trace("  Using getID()...");
	if (copy->getID() == "data")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, ID copy incorrect");
		fail += 1;
	}
    logger->trace("  Using getMsg()...");
	if (copy->getMsg() == "SubZero rox")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, Msg copy incorrect");
		fail += 1;
	}
    logger->trace("  Showing imgs using showImg()...");
    logger->trace("  If both imgs are identical press spacebar, else press esc...");
	data->showImg("data");
	copy->showImg("copy");
	char key;
	while (1) {
		key = cvWaitKey(0);
		if (char(key) == 32) {
            logger->trace("    ok");
			break;
		}
		else if (char(key) == 27) {
            logger->warn("    NOT ok, img not same");
			fail++;
			break;
		}
	}

    logger->trace(" Changing msg of copy to \"whatever\"...");
	copy->setMsg("whatever");

//	logger->trace(" Changing org img content...");
//	data->closeImg();
//	copy->closeImg();
//	img = ImgDataTEST::camCap();
//	cvDestroyWindow("camCap");
//	data->setImg(&img);

    logger->trace(" Checking variables...");
    logger->trace("  Using getMsg() on original...");
	if (copy->getMsg() == "whatever" && data->getMsg() == "SubZero rox")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, org or copy Msg incorrect");
		fail += 1;
	}
    logger->trace(" Using refcount to check independence...");
	int datarc, copyrc;
    datarc = data->img.u->refcount;
    copyrc = copy->img.u->refcount;
    logger->trace("    \"data\" img refcount: "+StringTools::intToStr(datarc));
    logger->trace("    \"copy\" img refcount: "+StringTools::intToStr(copyrc));
	if (datarc==2 && copyrc ==1) {
        logger->trace("    ok");
		fail--;
	}
	else if (datarc==3)
        logger->warn("    NOT ok, copy's img points to data's img obj");
	else
        logger->warn("    NOT ok, data ref should be 2, copy ref should be 1");
	fail++;
//	logger->trace("  Showing imgs using showImg()...");
//	data->showImg("data");
//	copy->showImg("copy");
//	logger->trace("  If copy different from data then deep copy ok press spacebar, else press esc...");
//	while (1) {
//		key = cvWaitKey(0);
//		if (char(key) == 32) {
//			logger->trace("    ok");
//			break;
//		}
//		else if (char(key) == 27) {
//			logger->warn("    NOT ok, img not same");
//			fail++;
//			break;
//		}
//	}
    logger->trace("Test complete.");
    logger->trace("Deleting data...");
	delete data;
	delete copy;

	if (fail > 0)
        logger->warn("  TEST FAILED: ImgData Copy Constructor");
    logger->trace("==============================");
	return fail;
}
