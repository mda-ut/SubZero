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
#include "PropertyReader.h"

using namespace std;

int main(int argc, char** argv) {
    QApplication app(argc, argv);
	Timer* logTimer = new Timer();
    Logger logger("Main");
    Logger::initialize(Logger::Level::INFO,true, true, logTimer);
    logger.trace("Logger initialized.");
    PropertyReader* settings;
    if (argc > 1) {
        settings = new PropertyReader(argv[1]);
    } else {
        settings = new PropertyReader("../SubZero/src/settings/settings.txt");
    }
    // Load properties
    settings->load();

    // Set logging level
    std::string loggingLevel = settings->getProperty("LOGGING_LEVEL");
    if (loggingLevel == "TRACE") {
        Logger::setLoggingLevel(Logger::Level::TRACE);
    } else if (loggingLevel == "INFO") {
        Logger::setLoggingLevel(Logger::Level::INFO);
    } else if (loggingLevel == "DEBUG") {
        Logger::setLoggingLevel(Logger::Level::DEBUG);
    } else if (loggingLevel == "WARN") {
        Logger::setLoggingLevel(Logger::Level::WARN);
    } else if (loggingLevel == "ERROR") {
        Logger::setLoggingLevel(Logger::Level::ERROR);
    }

    // Set default HSV Filter values
    if (!settings->getProperty("LOW_HUE").empty()) {
        HSVFilter::defaultLowH = std::stoi(settings->getProperty("LOW_HUE"));
    }
    if (!settings->getProperty("HIGH_HUE").empty()) {
        HSVFilter::defaultHighH = std::stoi(settings->getProperty("HIGH_HUE"));
    }
    if (!settings->getProperty("LOW_SATURATION").empty()) {
        HSVFilter::defaultLowS = std::stoi(settings->getProperty("LOW_SATURATION"));
    }
    if (!settings->getProperty("HIGH_SATURATION").empty()) {
        HSVFilter::defaultHighS = std::stoi(settings->getProperty("HIGH_SATURATION"));
    }
    if (!settings->getProperty("LOW_VALUE").empty()) {
        HSVFilter::defaultLowV = std::stoi(settings->getProperty("LOW_VALUE"));
    }
    if (!settings->getProperty("HIGH_VALUE").empty()) {
        HSVFilter::defaultHighV = std::stoi(settings->getProperty("HIGH_VALUE"));
    }

//    VideoTesting vt(0);
//    vt.run();

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
/*
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
*/
    /*
    int error = app.exec();
    //delete settings;
    return error;
    */
    return app.exec();
}

