/*
 * Main.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include <QApplication>
#include <string>
#include "util/Logger.h"
#include "scripts.h"
#include "Properties.h"
#include "PropertyReader.h"
#include "SubZeroFactory.h"
#include "Stage.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);
	Timer* logTimer = new Timer();
    Logger logger("Main");
    Logger::initialize(Logger::Level::TRACE,true, true, logTimer);
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

    init_signal_handler();

    SubZeroFactory* subZeroFactory = new SubZeroFactory(settings);
    Stage* mainStage = new Stage(NULL, subZeroFactory);

    mainStage->setViewContent(mode);
    mainStage->initialize();


    if (mode == "AUTONOMOUS") {
        //TODO: Make autonomous run without any GUI
        return 0;
    }

    delete propReader;
    return app.exec();
}

