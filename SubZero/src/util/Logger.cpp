/*
 * Logger.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Logger.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include <qdir.h>
#include "Util.h"

bool Logger::writeToConsole = true;
bool Logger::writeToFile = false;
std::ofstream Logger::logFile;
Timer* Logger::timer = NULL;
Logger::Level Logger::level = Logger::Level::DEBUG;

Logger::Logger(std::string className) {
    this->className = className;
}

void Logger::setLoggingLevel(Level level) {
    Logger::level = level;
}

bool Logger::initialize(Level level, bool writeToConsole, bool writeToFile, Timer* timer) {
    Logger::level = level;
    Logger::writeToConsole = writeToConsole;
	Logger::writeToFile = writeToFile;
	Logger::timer = timer;

	if (writeToFile) {
		char buffer[80];
        strftime(buffer, 80, "%I:%M:%S_%d-%m-%Y.log", timer->getTimeStamp());

		std::string logName(buffer);

        //Create a logs folder if one does not exist and places a log file into
        QString test= QString::fromStdString(Util::getWorkingDirectory());
        QDir dir(test);

        if (!(QDir(QString::fromStdString(Util::getWorkingDirectory()+"/logs")).exists())) {
            dir.mkpath("logs");
        }

        logName = Util::getWorkingDirectory() + "/logs/"+ logName;

		logFile.open(logName.c_str());
		if (!logFile.is_open()) {
			std::cout << "Unable to create log file." << std::endl;
            return false;
		}
	}

	return true;

}

void Logger::trace(std::string msg) {
    if (Level::TRACE >= Logger::level) {
        char buffer[100];
        std::string output = "%d-%m-%Y %I:%M:%S\t" + className + "\t\tTRACE\t";
        strftime(buffer, 100, output.c_str(), timer->getTimeStamp());

        std::string finalMsg(buffer);
        finalMsg += msg;
        log(finalMsg);
    }
}

void Logger::info(std::string msg) {
    if (Level::INFO >= Logger::level) {
        char buffer[100];
        std::string output = "%d-%m-%Y %I:%M:%S\t" + className + "\t\tINFO\t";
        strftime(buffer, 100, output.c_str(), timer->getTimeStamp());

        std::string finalMsg(buffer);
        finalMsg += msg;
        log(finalMsg);
    }
}

void Logger::debug(std::string msg) {
    if (Level::DEBUG >= Logger::level) {
        char buffer[100];
        std::string output = "%d-%m-%Y %I:%M:%S\t" + className + "\t\tDEBUG\t";
        strftime(buffer, 100, output.c_str(), timer->getTimeStamp());

        std::string finalMsg(buffer);
        finalMsg += msg;
        log(finalMsg);
    }
}

void Logger::warn(std::string msg) {
    if (Level::WARN >= Logger::level) {
        char buffer[100];
        std::string output = "%d-%m-%Y %I:%M:%S\t" + className + "\t\tWARN\t";
        strftime(buffer, 100, output.c_str(), timer->getTimeStamp());

        std::string finalMsg(buffer);
        finalMsg += msg;
        log(finalMsg);
    }
}

void Logger::error(std::string msg) {
    if (Level::ERROR >= Logger::level) {
        char buffer[100];
        std::string output = "%d-%m-%Y %I:%M:%S\t" + className + "\t\tERROR\t";
        strftime(buffer, 100, output.c_str(), timer->getTimeStamp());

        std::string finalMsg(buffer);
        finalMsg += msg;
        log(finalMsg);
    }
}

void Logger::log(std::string msg) {
	if (writeToConsole) {
		std::cout << msg << std::endl;
	}

	if (writeToFile) {
		logFile << msg << std::endl;
	}
}

void Logger::close() {
	logFile.close();
	delete timer;
}

Logger::~Logger() {

}
