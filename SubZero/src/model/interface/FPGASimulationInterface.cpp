/*
 * FPGASimulationInterface.cpp
 *
 *  Created on: Jul 7, 2015
 *      Author: ahsueh1996
 */


#include "FPGASimulationInterface.h"
#include <sstream>
#include <string>
#include <iterator>
#include "scripts_sim.h"


/* ==========================================================================
 * 				INTERACTING WITH DATA COMING IN (FROM FPGA)
 * ==========================================================================
 * This interface class will be automatically polling and managing
 * the polling process privately within the interface at pollFrequency
 * using the functions below.
 */

void FPGASimulationInterface::poll() {
    double depth = (double) get_depth_sim();
    double heading = (double) get_yaw_sim();
    int accel_x, accel_y, accel_z;
    logger->trace("get accel");

    get_accel_sim(&accel_x, &accel_y, &accel_z);
    //need to adjust code for accel rather than speed

    logger->trace(StringTools::intToStr(accel_x));
    logger->trace(StringTools::intToStr(accel_y));
    logger->trace(StringTools::intToStr(accel_z));

    std::string in;
    logger->trace("b for break\n");
    while (1) {
        getline(std::cin,in);
        if (in =="b")
            break;
    }

    Data* new_data = new FPGAData("raw", depth, 0, heading);
    this->storeToBuffer(new_data);
}

FPGAData* FPGASimulationInterface::decode(std::string* data) {

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
}

void FPGASimulationInterface::in() {

    std::cout<<"in"<<std::endl;

    struct timespec tictoc;
    clock_gettime(CLOCK_MONOTONIC, &tictoc);

    while(executing) {
//        logger->trace("in while");
        // setting period of polling and auto-clearing
        // iterate once every this many seconds
        tictoc.tv_nsec += (long) (1000000000 / pollFrequency);
        tictoc.tv_sec += (time_t) (tictoc.tv_nsec /1000000000);
        tictoc.tv_nsec = tictoc.tv_nsec % 1000000000;
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &tictoc, NULL);
        //std::cout<<"poll"<<std::endl;
        logger->trace("poll");
        this->poll();

    }
}


/* ==========================================================================
 * 				INTERACTING WITH DATA GOING OUT (TO FPGA)
 * ==========================================================================
 * FPGASimulationInterface provides functions for the Controller to send data/commands/
 * messages to the FPGA.
 */

void FPGASimulationInterface::set(Attributes attr, int value) {
    std::cout << attr << ":" << value << std::endl;
    switch(attr) {
    case POWER:
        if (value == 0) {
            power_off_sim();
        } else if (value == 1){
            power_on_sim();
        } else {
            logger->trace("Error: wrong power value of " + std::to_string(value));
        }
        break;
    case DEPTH:
        dyn_set_target_depth_sim(value);
        break;
    case HEADING:
        dyn_set_target_yaw_sim(value);
        break;
    case YAW:
        dyn_set_target_yaw_sim(value);
        break;
    case SPEED:
        dyn_set_target_speed_sim(value);
        break;
    default:
        break;
    }

}

// for method 2: using libusb
void FPGASimulationInterface::send(std::string* data) {

}

/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */


FPGASimulationInterface::FPGASimulationInterface(int bufferSize, int pollFrequency) {

    this->bufferSize = bufferSize;
    this->pollFrequency = pollFrequency;

    // thread for reading and polling FPGA input
    // main thread will listen for commands to be sent to FPGA
//   readThreads.push_back(std::thread(&FPGASimulationInterface::in, this));
}

void FPGASimulationInterface::init() {
    logger->trace("init");
    init_fpga_sim();
    logger->trace("verbose");
    set_verbose_sim(0);
    executing = true;
    logger->trace("thread make");
    readThreads.push_back(std::thread(&FPGASimulationInterface::in, this));
}

FPGASimulationInterface::~FPGASimulationInterface() {
    // join readThread with main
    executing = false;
    exit_safe_sim();

    //calls HwInterfaces dtor afterwards
}
