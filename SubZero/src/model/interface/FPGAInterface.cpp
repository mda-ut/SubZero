/*
 * FPGAInterface.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "FPGAInterface.h"
#include <sstream>
#include <iterator>


/* ==========================================================================
 * 				INTERACTING WITH DATA COMING IN (FROM FPGA)
 * ==========================================================================
 * This interface class will be automatically polling and managing
 * the polling process privately within the interface at pollFrequency
 * using the functions below.
 */

void FPGAInterface::poll() {

    std::string raw;
    std::cin >> raw;
    Data* decoded = this->decode(&raw);
    this->storeToBuffer(decoded);

};

FPGAData* FPGAInterface::decode(std::string* data) {

    std::istringstream iss(*data);
    std::istream_iterator<std::string> begin(iss), end;
    std::vector<std::string> attributes(begin, end);

    std::string::size_type size;

    // Right now we only have three attributes from FPGA
    // depth = attributes[0]
    // speed = attributes[1]
    // heading = attributes[2]
    // is it possible to not hardcode this?
    double depth = std::stod (attributes[0], &size);
    double speed = std::stod (attributes[1], &size);
    double heading = std::stod (attributes[2], &size);
    // Note: for stod (string to double conversion)
    //       need to compile with -std=c++11

    FPGAData* decoded = new FPGAData("raw", depth, speed, heading);

    return decoded;
};

/* ==========================================================================
 * 				INTERACTING WITH DATA GOING OUT (TO FPGA)
 * ==========================================================================
 * FPGAInterface provides functions for the Controller to send data/commands/
 * messages to the FPGA.
 */

void FPGAInterface::set(Attributes attr, int value) {
    std::cout << attr << ":" << value << std::endl;
}

// for method 2: using libusb
void FPGAInterface::send(std::string* data) {

};

/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */


FPGAInterface::FPGAInterface(int bufferSize, int pollFrequency) {

    this->bufferSize = bufferSize;
    this->pollFrequency = pollFrequency;

    // thread for reading and polling FPGA input
    // main thread will listen for commands to be sent to FPGA
   readThreads.push_back(std::thread(&FPGAInterface::in, this));

}

FPGAInterface::~FPGAInterface() {

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
