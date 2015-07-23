/*
 * Timer.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <cstdint>
#include <ctime>
#include <sys/time.h>

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
    uint64_t start();

	/**
	 * Stops the timer.
	 * @return The current time and -1 if failed
	 */
    uint64_t stop();

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
    uint64_t getCurrentTime();

    struct tm* getTimeStamp();

	virtual ~Timer();

private:
    uint64_t startTime;
    uint64_t endTime;
};

#endif /* TIMER_H_ */
