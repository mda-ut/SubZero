/*
 * Logger.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "Timer.h"
#include <string>

/**
 * This class takes care of logging.  It currently is not thread safe and race conditions may occur during logging.
 */
class Logger {
public:
	Logger();

	/**
	 * Initializes the logger with specified parameters.  Must be called before use of the logger.
	 *
	 * @param writeToConsole flag for logging to console
	 * @param writeToFile flag for logging to file
	 * @param timer pointer to a timer to be used for logging.  Do not share timers with other classes.
	 * @return true if the logger was initialized successfully, false otherwise
	 */
	static bool initialize(bool writeToConsole, bool writeToFile, Timer* timer);

	/**
	 * Logs the message at the TRACE level.
	 *
	 * @param msg
	 */
	static void trace(std::string msg);

	/**
	 * Logs the message at the INFO level.
	 *
	 * @param msg
	 */
	static void info(std::string msg);

	/**
	 * Logs the message at the DEBUG level.
	 *
	 * @param msg
	 */
	static void debug(std::string msg);

	/**
	 * Logs the message at the WARN level.
	 *
	 * @param msg
	 */
	static void warn(std::string msg);

	/**
	 * Logs the message at the ERROR level.
	 *
	 * @param msg
	 */
	static void error(std::string msg);

	/**
	 * Closes the Logger and closes and deletes anything associated to it.
	 */
	static void close();
	virtual ~Logger();

protected:
	/**
	 * Logs the message.
	 *
	 * @param msg
	 */
	static void log(std::string msg);

private:
	static Timer* timer;
	static bool writeToFile;
	static std::ofstream logFile;
	static bool writeToConsole;
};

#endif /* LOGGER_H_ */
