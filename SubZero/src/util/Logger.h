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

    enum Level {TRACE, DEBUG, INFO, WARN, ERROR, OFF};

    /**
     * @brief Logger Constructs a logger.  This logger MUST be initialized.
     * @param className Name of the class the logger is from
     */
    Logger(std::string className);

    /**
     * @brief setLoggingLevel Changes the current logging level to the specified logging level
     * @param level New logging level for logger to be set to
     */
    static void setLoggingLevel(Level level);

	/**
	 * Initializes the logger with specified parameters.  Must be called before use of the logger.
	 *
     * @param level logging level to be set to
     * @param writeToConsole flag for logging to console
	 * @param writeToFile flag for logging to file
	 * @param timer pointer to a timer to be used for logging.  Do not share timers with other classes.
	 * @return true if the logger was initialized successfully, false otherwise
	 */
    static bool initialize(Level level, bool writeToConsole, bool writeToFile, Timer* timer);

	/**
	 * Logs the message at the TRACE level.
	 *
	 * @param msg
	 */
    void trace(std::string msg);

	/**
	 * Logs the message at the INFO level.
	 *
	 * @param msg
	 */
    void info(std::string msg);

	/**
	 * Logs the message at the DEBUG level.
	 *
	 * @param msg
	 */
    void debug(std::string msg);

	/**
	 * Logs the message at the WARN level.
	 *
	 * @param msg
	 */
    void warn(std::string msg);

	/**
	 * Logs the message at the ERROR level.
	 *
	 * @param msg
	 */
    void error(std::string msg);

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
    static bool writeToConsole;
	static std::ofstream logFile;
    static Level level;
    std::string className;
};

#endif /* LOGGER_H_ */
