/*
 * Main.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "util/Logger.h"
#include <string>
#include "view/menu.h"
#include "controller/controllers/Controller.h"
#include <QApplication>
#include <iostream>
#include "../test/VideoTesting.h"
#include "../test/CollectionTEST.h"
#include "model/state/StateTester.h"
#include "FPGAInterface.h"
#include "CameraInterface.h"

using namespace std;

int main(int argc, char** argv) {
    //QApplication app(argc, argv);
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("Logger initialized.");	
    QApplication app(argc, argv);
//    Menu* newMenu = new Menu;
//    newMenu->show();

//    newMenu.paintEvent();
//    VideoTesting vt("videofile");
//    vt.run();
//    CollectionTEST::runDataAndFilterManagerCollection();
//    CollectionTEST::runFilterCollection(); //commented a crash line in here... uncomment to reproduce

//    StateTester::run();
//    FPGAInterface newInterface(20, 1);
//    Logger::close();
//    delete logTimer;

    CameraInterface newCam(20, 25, FRONT);
    CameraInterface downCam(20, 25, DOWN);
    newCam.init();
    downCam.init();
    while(1) {
        ImgData* newCamData = dynamic_cast<ImgData*>(newCam.getDataFromBuffer());
        ImgData* downCamData = dynamic_cast<ImgData*>(downCam.getDataFromBuffer());

        if(newCamData!=0 && downCamData !=0) {
            ImgData camDataCopy(*newCamData);
            ImgData downDataCopy(*downCamData);

            //Logger::trace("showing image " + camDataCopy.getID());
            camDataCopy.showImg("current");
            downDataCopy.showImg("down");
        }
    }


    return 0;//app.exec();
}

