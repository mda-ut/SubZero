/*
 * Logger.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Logger.h"
#include "Timer.h"
#include <iostream>

bool Logger::writeToConsole = true;
bool Logger::writeToFile = false;
Timer* Logger::timer = NULL;

Logger::Logger() {
	// TODO Auto-generated constructor stub

}

void Logger::initialize(bool writeToConsole, bool writeToFile, Timer* timer) {
	Logger::writeToConsole = writeToConsole;
	Logger::writeToFile = writeToFile;
	Logger::timer = timer;

	char buffer[80];
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timer->getCurrentTime());

	std::string logName(buffer);

	//TODO: Create log file.
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
	strftime(buffer, 100, "%d-%m-%Y %I:%M:%S\tINFO\t",
			timer->getCurrentTime());

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
	strftime(buffer, 100, "%d-%m-%Y %I:%M:%S\tWARN\t",
			timer->getCurrentTime());

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
		//TODO: Add functionality to write to file.
	}
}

Logger::~Logger() {
	delete timer;
}
