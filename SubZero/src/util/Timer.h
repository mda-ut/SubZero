/*
 * Timer.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <ctime>

/**
 * The Timer class takes care of managing the current time.
 */
class Timer {
public:
	Timer();

	/**
	 * Starts the timer.
	 * @return The current time and -1 if failed
	 */
	time_t start();

	/**
	 * Stops the timer.
	 * @return The current time and -1 if failed
	 */
	time_t stop();

	/**
	 * Returns the number of seconds that have elapsed since timer started.
	 * @return The number of seconds that have elapsed since the timer started
	 */
	double getTimeElapsed();

	/**
	 * Returns the number of seconds passed between the start and stop times.
	 * @return The number of seconds that have passed since the timer started and the timer stopped
	 */
	double getTimeDiff();

	/**
	 * Returns the current time.
	 * @return The current time and NULL if failed
	 */
	struct tm* getCurrentTime();

	virtual ~Timer();

private:
	time_t startTime;
	time_t endTime;
	time_t currTime;
};

#endif /* TIMER_H_ */
