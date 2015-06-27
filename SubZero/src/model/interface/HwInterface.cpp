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
    this->decodedBuffer.pop();
};


void HwInterface::storeToBuffer(Data* data) {
    this->decodedBuffer.push(data);
}

void HwInterface::in() {

    struct timespec tictoc;
    clock_gettime(CLOCK_MONOTONIC, &tictoc);

    while (true) {

        // setting period of polling and auto-clearing
        // iterate once every this many seconds
        tictoc.tv_nsec += (long) (1000000000 / pollFrequency);
        tictoc.tv_sec += (time_t) (tictoc.tv_nsec /1000000000);
        tictoc.tv_nsec = tictoc.tv_nsec % 1000000000;
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &tictoc, NULL);

        if ( decodedBuffer.size() >= bufferSize) {
            // delete old stuff from buffer
            this->deleteFromBuffer();
        }

        this->poll();

    }
}

/* ==========================================================================
 * 								GETTERS AND SETTERS
 * ==========================================================================
 */

Data* HwInterface::getDataFromBuffer() {
    Data* data = new Data("bad");
    if (! (this->decodedBuffer).empty()) {
        data = &(this->decodedBuffer.back());
    } else {
        std::cout << "Nothing in buffer";
    }
    return data;
};

int HwInterface::getPollFrequency() {
    return this->pollFrequency;
};

void HwInterface::setPollFrequency(int frequency){
    this->pollFrequency = frequency;
};


int HwInterface::getBufferSize(){
    return this->bufferSize;
};

void HwInterface::setBufferSize(int bufferSize) {
    this->bufferSize = bufferSize;
};


/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */

HwInterface::HwInterface(){}

HwInterface::HwInterface(int bufferSize, int pollFrequency) {

    this->bufferSize = bufferSize;
    this->pollFrequency = pollFrequency;

    // thread for reading and polling Hw input
    // main thread will listen for commands to be sent to Hw
   readThreads.push_back(std::thread(&HwInterface::in, this));

}

HwInterface::~HwInterface() {

    // join readThread with main
    for(auto& t: readThreads) {t.join();}

    // clears the queue
    while ( ! decodedBuffer.empty()) {
        decodedBuffer.pop();
    }
    // not sure if the above also frees up memory used up by the "queue container"
    // whatever the container may be... delete it by following the pointer
    delete &(this->decodedBuffer);
    delete &(this->bufferSize);
    delete &(this->pollFrequency);

}
