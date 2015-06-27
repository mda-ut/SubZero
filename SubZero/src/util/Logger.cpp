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
#include "util/Util.h"

bool Logger::writeToConsole = true;
bool Logger::writeToFile = false;
std::ofstream Logger::logFile;
Timer* Logger::timer = NULL;

Logger::Logger() {
	// TODO Auto-generated constructor stub
}

bool Logger::initialize(bool writeToConsole, bool writeToFile, Timer* timer) {
	Logger::writeToConsole = writeToConsole;
	Logger::writeToFile = writeToFile;
	Logger::timer = timer;

	if (writeToFile) {
		char buffer[80];
		strftime(buffer, 80, "%d-%m-%Y_%I:%M:%S.log", timer->getCurrentTime());

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
	char buffer[100];
	strftime(buffer, 100, "%d-%m-%Y %I:%M:%S\tTRACE\t",
			timer->getCurrentTime());

	std::string finalMsg(buffer);
	finalMsg += msg;
	log(finalMsg);
}

void Logger::info(std::string msg) {
	char buffer[100];
	strftime(buffer, 100, "%d-%m-%Y %I:%M:%S\tINFO\t", timer->getCurrentTime());

	std::string finalMsg(buffer);
	finalMsg += msg;
	log(finalMsg);
}

void Logger::debug(std::string msg) {
	char buffer[100];
	strftime(buffer, 100, "%d-%m-%Y %I:%M:%S\tDEBUG\t",
			timer->getCurrentTime());

	std::string finalMsg(buffer);
	finalMsg += msg;
	log(finalMsg);
}

void Logger::warn(std::string msg) {
	char buffer[100];
	strftime(buffer, 100, "%d-%m-%Y %I:%M:%S\tWARN\t", timer->getCurrentTime());

	std::string finalMsg(buffer);
	finalMsg += msg;
	log(finalMsg);
}

void Logger::error(std::string msg) {
	char buffer[100];
	strftime(buffer, 100, "%d-%m-%Y %I:%M:%S\tERROR\t",
			timer->getCurrentTime());

	std::string finalMsg(buffer);
	finalMsg += msg;
	log(finalMsg);
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
