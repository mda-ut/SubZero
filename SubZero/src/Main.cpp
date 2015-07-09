/*
 * Main.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "util/Logger.h"
#include <string>
#include "Stage.h"
#include "MenuView.h"
#include "GUIView.h"
#include <QApplication>
#include "Properties.h"
#include "PropertyReader.h"

using namespace std;

int main(int argc, char** argv) {
    QApplication app(argc, argv);
	Timer* logTimer = new Timer();
    Logger logger("Main");
    Logger::initialize(Logger::Level::INFO,true, true, logTimer);
    logger.trace("Logger initialized.");
    PropertyReader* propReader;
    Properties* settings;
    if (argc > 1) {
        propReader = new PropertyReader(argv[1]);
    } else {
        propReader = new PropertyReader("../SubZero/src/settings/settings.txt");
    }
    settings = propReader->load();
    std::string loggingLevel = settings->getProperty("LOGGING_LEVEL");
    if (loggingLevel == "OFF") {
        Logger::setLoggingLevel(Logger::Level::OFF);
    } else if (loggingLevel == "TRACE") {
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

    std::string mode = settings->getProperty("MODE");

    if (mode == "MENU") {
        Stage* mainStage = new Stage();
        // Temporary declaration to test
        Controller* controller = new Controller();
        controller->setStage(mainStage);
        mainStage->initialize();
        mainStage->setViewContent(new MenuView(controller));
        mainStage->show();
    } else if (mode == "GUI") {
        Stage* mainStage = new Stage();
        // Temporary declaration to test
        Controller* controller = new Controller();
        controller->setStage(mainStage);
        mainStage->initialize();
        mainStage->setViewContent(new GUIView(controller));
        mainStage->show();
    } else if (mode == "SIMULATOR") {
        //TODO: Make Simulator View
    } else if (mode == "AUTONOMOUS") {
        //TODO: Make autonomous run without any GUI
        return 0;
    }

    return app.exec();
}

