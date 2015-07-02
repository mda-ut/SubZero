/*
 * HwInterface.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "HwInterface.h"
#include <sstream>
#include <iterator>
#include <iostream>
#include <unistd.h>


/* ==========================================================================
 * 							MANAGING DATA BUFFER
 * ==========================================================================
 * The data buffer will be managed automatically and privately by this class.
 * These functions are defined and implemented in the root parent class i.e.
 * in HwInterface.
 */

void HwInterface::deleteFromBuffer() {
    delete decodedBuffer.front();
    decodedBuffer.pop();
}


void HwInterface::storeToBuffer(Data* data) {
    if (decodedBuffer.size() >= bufferSize) {
        // delete old stuff from buffer
        deleteFromBuffer();
    }
    decodedBuffer.push(data);
}

void HwInterface::in() {
    logger->info("Executing");

    struct timespec tictoc;
    clock_gettime(CLOCK_MONOTONIC, &tictoc);

    while(executing) {

        // setting period of polling and auto-clearing
        // iterate once every this many seconds
        tictoc.tv_nsec += (long) (1000000000 / pollFrequency);
        tictoc.tv_sec += (time_t) (tictoc.tv_nsec /1000000000);
        tictoc.tv_nsec = tictoc.tv_nsec % 1000000000;
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &tictoc, NULL);
        poll();

    }
}

/* ==========================================================================
 * 								GETTERS AND SETTERS
 * ==========================================================================
 */


/*
Data* HwInterface::getDataFromBuffer() {
    Data* data = nullptr;
    if (!(this->decodedBuffer.empty())) {
        data = this->decodedBuffer.back();
    } else {
        std::cout << "Nothing in buffer"<<std::endl;
    }
    return data;
}*/

int HwInterface::getPollFrequency() {
    return pollFrequency;
}

void HwInterface::setPollFrequency(int frequency){
    pollFrequency = frequency;
}

int HwInterface::getBufferSize(){
    return bufferSize;
}

void HwInterface::setBufferSize(int bufferSize) {
    bufferSize = bufferSize;
}


/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */

HwInterface::HwInterface() {

}

HwInterface::HwInterface(int bufferSize, int pollFrequency) {

    this->bufferSize = bufferSize;
    this->pollFrequency = pollFrequency;
}

void HwInterface::init() {
    // thread for reading and polling Hw input
    // main thread will listen for commands to be sent to Hw
   readThreads.push_back(std::thread(&HwInterface::in, this));
   logger->info("Thread started");
}

HwInterface::~HwInterface() {
    delete logger;
}
