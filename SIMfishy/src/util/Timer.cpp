/*
 * Timer.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Timer.h"

Timer::Timer() {
    startTime = time(0);
    endTime = time(0);
    currTime = time(0);

}

time_t Timer::start() {
	if (time(&startTime) != -1) {
		return startTime;
	} else {
		return -1;
	}
}

time_t Timer::stop() {
	if (time(&endTime) != -1) {
		return endTime;
	} else {
		return -1;
	}
}

double Timer::getTimeElapsed() {
    return difftime(startTime,time(0));
}

double Timer::getTimeDiff() {
	return difftime(startTime,endTime);
}

struct tm* Timer::getCurrentTime() {
	if (time(&currTime) != -1) {
		return localtime(&currTime);
	} else {
        return 0;
	}
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

