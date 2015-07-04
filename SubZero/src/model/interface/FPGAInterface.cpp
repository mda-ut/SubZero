/*
 * FPGAInterface.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "FPGAInterface.h"
#include <sstream>
#include <string>
#include <iterator>
#include "scripts.h"


/* ==========================================================================
 * 				INTERACTING WITH DATA COMING IN (FROM FPGA)
 * ==========================================================================
 * This interface class will be automatically polling and managing
 * the polling process privately within the interface at pollFrequency
 * using the functions below.
 */

void FPGAInterface::poll() {
    mutex.lock();
    //TODO Add error checking on values from FPGA
    int power = get_power();
    int depth = get_depth();
    int yaw = get_yaw();
    mutex.unlock();

    Data* new_data = new FPGAData("raw", power, yaw, depth);
    storeToBuffer(new_data);
}

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
    int depth = std::stod (attributes[0], &size);
    int speed = std::stod (attributes[1], &size);
    int heading = std::stod (attributes[2], &size);
    // Note: for stod (string to int conversion)
    //       need to compile with -std=c++11

    FPGAData* decoded = new FPGAData("raw", depth, speed, heading);

    return decoded;
}


/* ==========================================================================
 * 				INTERACTING WITH DATA GOING OUT (TO FPGA)
 * ==========================================================================
 * FPGAInterface provides functions for the Controller to send data/commands/
 * messages to the FPGA.
 */

void FPGAInterface::set(Attributes attr, int value) {
    logger->trace("Setting " + std::to_string(attr) + " to " + std::to_string(value));
    mutex.lock();
    switch(attr) {
    case POWER:
        if (value == 0) {
            power_off();
        } else if (value == 1) {
            power_on();
        } else {
            logger->warn("Invalid power value of " + std::to_string(value));
        }
        break;
    case DEPTH:
        dyn_set_target_depth(value);
        break;
    case YAW:
        dyn_set_target_yaw(value);
        break;
    case SPEED:
        dyn_set_target_speed(value);
        break;
    case MOTOR:
        startup_sequence();
        break;
    default:
        logger->warn("Invalid FPGA attribute of " + std::to_string(attr));
        break;
    }
    mutex.unlock();


}

// for method 2: using libusb
void FPGAInterface::send(std::string* data) {

}

/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */


FPGAInterface::FPGAInterface(int bufferSize, int pollFrequency, PropertyReader* settings) {
    this->bufferSize = bufferSize;
    this->pollFrequency = pollFrequency;
    this->settings = settings;
}

void FPGAInterface::init() {
    logger->info("Initializing FPGA connection");
    init_fpga();
    set_verbose(0);
    executing = true;

    double P, I, D, Alpha;
    P = std::stod(settings->getProperty("DEPTH_P"));
    I = std::stod(settings->getProperty("DEPTH_I"));
    D = std::stod(settings->getProperty("DEPTH_D"));
    Alpha = std::stod(settings->getProperty("DEPTH_ALPHA"));
    set_pid_depth(P, I, D, Alpha);

    P = std::stod(settings->getProperty("PITCH_P"));
    I = std::stod(settings->getProperty("PITCH_I"));
    D = std::stod(settings->getProperty("PITCH_D"));
    Alpha = std::stod(settings->getProperty("PITCH_ALPHA"));
    set_pid_pitch(P, I, D, Alpha);

    P = std::stod(settings->getProperty("ROLL_P"));
    I = std::stod(settings->getProperty("ROLL_I"));
    D = std::stod(settings->getProperty("ROLL_D"));
    Alpha = std::stod(settings->getProperty("ROLL_ALPHA"));
    set_pid_roll(P, I, D, Alpha);

    P = std::stod(settings->getProperty("YAW_P"));
    I = std::stod(settings->getProperty("YAW_I"));
    D = std::stod(settings->getProperty("YAW_D"));
    Alpha = std::stod(settings->getProperty("YAW_ALPHA"));
    set_pid_yaw(P, I, D, Alpha);

    // thread for reading and polling FPGA input
    // main thread will listen for commands to be sent to FPGA
    logger->info("Started a new thread to read and poll FPGA input");
    readThreads.push_back(std::thread(&FPGAInterface::in, this));
}

FPGAInterface::~FPGAInterface() {
    // join readThread with main
    executing = false;
    for(auto& t: readThreads) {
        t.join();
    }
    logger->info("Safely closing FPGA connection");
    exit_safe();

    delete logger;
}
