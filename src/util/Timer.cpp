/*
 * Timer.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Timer.h"

Timer::Timer() {
    startTime = getCurrentTime();
    endTime = startTime;
}

uint64_t Timer::start() {
    startTime = getCurrentTime();
    return startTime;
}

uint64_t Timer::stop() {
    endTime = getCurrentTime();
    return endTime;
}

double Timer::getTimeElapsed() {
    uint64_t currentTime = getCurrentTime();
    if (currentTime < startTime) {
        currentTime = startTime;
    }
    return (double) (getCurrentTime() - startTime) / 1000000000;
}

double Timer::getTimeDiff() {
    return (double) (endTime-startTime) / 1000000000; //convert nanoseconds to seconds
}

uint64_t Timer::getCurrentTime() {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    uint64_t seconds = (uint64_t) t.tv_sec;
    uint64_t currentTime = seconds*1000000000 + (uint64_t)t.tv_nsec;
    return currentTime;
}

struct tm* Timer::getTimeStamp() {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return localtime(&t.tv_sec);
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

