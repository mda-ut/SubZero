/*
 * Main.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "util/Logger.h"
#include <string>
#include "view/Menu.h"
#include "controller/controllers/Controller.h"
#include <QApplication>
#include <iostream>
#include "../test/VideoTesting.h"
#include "../test/CollectionTEST.h"
#include "model/state/StateTester.h"
#include "util/PropertyReader.h"
#include "model/CameraModel.h"

#include "util/VideoLogger.h"
#include <opencv2/videoio/videoio.hpp>

using namespace std;

int main(int argc, char** argv) {
    QApplication app(argc, argv);
	Timer* logTimer = new Timer();
    Logger logger("Main");
    Logger::initialize(Logger::Level::TRACE,true, true, logTimer);
    logger.trace("Logger initialized.");
    PropertyReader* settings;
    if (argc > 1) {
        settings = new PropertyReader(argv[1]);
    } else {
        settings = new PropertyReader("../../SubZero/src/settings/settings.txt");
    }
    settings->load();
    Menu* newMenu = new Menu(settings);
    newMenu->show();

//    newMenu.paintEvent();
//    VideoTesting vt("videofile");
//    vt.run();
//    CollectionTEST::runDataAndFilterManagerCollection();
//    CollectionTEST::runFilterCollection(); //commented a crash line in here... uncomment to reproduce

//    StateTester::run();
//    FPGAInterface newInterface(20, 1);
//    Logger::close();
//    delete logTimer;

    VideoLogger* vLog = new VideoLogger("testvid",600,480,24);
    CameraInterface* newCam = new CameraInterface(20, 25, 0);
////    CameraInterface downCam(20, 25, DOWN);
    newCam->init();
////    downCam.init();

//    ImgData* sizeImg = dynamic_cast<ImgData*>(newCam->getDataFromBuffer());
//    cv::Size size(1000,1000);//(sizeImg->getWidth(),sizeImg->getHeight());
//    cv::VideoWriter vWri("~/Documents/git/SubZero/testTEST.mpeg",CV_FOURCC('m','p','e','g'),20,size);
//    if (!vWri.isOpened())
//        logger.trace("not opened... not cool");
//    cv::waitKey(0);
    logger.trace("continue");
    while(1) {
        ImgData* newCamData = dynamic_cast<ImgData*>(newCam->getDataFromBuffer());
////        ImgData* downCamData = dynamic_cast<ImgData*>(downCam.getDataFromBuffer());

        if(newCamData!=0 /*&& downCamData !=0*/) {
            ImgData camDataCopy(*newCamData);
////            ImgData downDataCopy(*downCamData);
            vLog->write(camDataCopy);
            logger.trace("written");
//            vWri.write(camDataCopy.getImg());
            //Logger::trace("showing image " + camDataCopy.getID());
            camDataCopy.showImg("current");

////            downDataCopy.showImg("down");
        char key;
        key = cv::waitKey(10);
        if (key == 27)
            break;
        }
    }
    cv::destroyWindow("current");
    delete vLog;
//    vWri.release();
    int error = app.exec();
    //delete settings;
    return error;
}

