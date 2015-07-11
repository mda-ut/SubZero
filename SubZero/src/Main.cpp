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
#include "model/interface/FPGASimulationInterface.h"

#include "util/PropertyReader.h"
#include "model/CameraModel.h"

#include "util/VideoLogger.h"
#include <opencv2/videoio/videoio.hpp>



#include <curses.h>

#include <assert.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


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



//    VideoLogger* vLog = new VideoLogger("testvid",600,480,24);
//    CameraInterface* newCam = new CameraInterface(20, 25, 0);
////    CameraInterface downCam(20, 25, DOWN);
//    newCam->init();
////    downCam.init();
//    while(1) {
//        ImgData* newCamData = dynamic_cast<ImgData*>(newCam->getDataFromBuffer());
////        ImgData* downCamData = dynamic_cast<ImgData*>(downCam.getDataFromBuffer());

//        if(newCamData!=0 /*&& downCamData !=0*/) {
//            ImgData camDataCopy(*newCamData);
////            ImgData downDataCopy(*downCamData);
//            vLog->write(camDataCopy);
//            camDataCopy.showImg("current");
////            downDataCopy.showImg("down");
//        char key;
//        key = cv::waitKey(10);
//        if (key == 27)
//            break;
//        }
//    }
//    cv::destroyWindow("current");
//    delete vLog;

    int error = app.exec();

    /*
    FILE* infp,*outfp;

    infp = std::fopen("infp.txt","w");
    std::fprintf(infp,"gax\n");
//    fclose(infp);
    fflush(infp);
    outfp = std::fopen("outfp.txt","r");
    char buf[158];
    std::string mystr;
    long size = 0;
    while (1)
    {
        std::rewind(outfp);
        std::fseek(outfp,0,SEEK_END);
        size = std::ftell(outfp);
        std::rewind(outfp);
        if (size > 0) {
            std::fgets(buf,158,outfp);
            printf("%s\n",buf);
            if (std::string(buf) == "gax\n")
                break;
            else
                logger.trace("not gax");
        }
    }
    */

    FPGASimulationInterface interface(20,1);
    interface.init();


//    int* x;
//    std::fscanf(outfp,"%d",x);
//    logger.trace(StringTools::intToStr(*x));
//    fclose(infp);
//    fclose(outfp);
 //    delete interface;

    std::string in;
    logger.trace("m for break\n");
    while (1) {
        getline(std::cin,in);
        if (in =="m")
            break;
    }

    return error;
}

