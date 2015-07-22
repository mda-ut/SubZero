/*
 * FPGAInterface.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "SimFPGAInterface.h"
#include <string>


/* ==========================================================================
 * 				INTERACTING WITH DATA COMING IN (FROM FPGA)
 * ==========================================================================
 * This interface class will be automatically polling and managing
 * the polling process privately within the interface at pollFrequency
 * using the functions below.
 */

FPGAData* SimFPGAInterface::poll() {
    mutex.lock();
    //TODO Add error checking on values from FPGA
    int power = simFPGA->get_power();
    int depth = simFPGA->get_depth();
    int yaw = simFPGA->get_yaw();
    mutex.unlock();

    return new FPGAData("raw", power, yaw, depth);
}


/* ==========================================================================
 * 				INTERACTING WITH DATA GOING OUT (TO FPGA)
 * ==========================================================================
 * FPGAInterface provides functions for the Controller to send data/commands/
 * messages to the FPGA.
 */

void SimFPGAInterface::set(Attributes attr, int value) {
    logger->trace("Setting " + std::to_string(attr) + " to " + std::to_string(value));
    mutex.lock();
    switch(attr) {
    case POWER:
        if (value == 0) {
            simFPGA->power_off();
        } else if (value == 1) {
            simFPGA->power_on();
        } else {
            logger->warn("Invalid power value of " + std::to_string(value));
        }
        break;
    case DEPTH:
        simFPGA->set_target_depth(value);
        break;
    case YAW:
        simFPGA->set_target_yaw(value);
        break;
    case SPEED:
        simFPGA->set_target_speed(value);
        break;
    case MOTOR:
        simFPGA->startup_sequence();
        break;
    default:
        logger->warn("Invalid FPGA attribute of " + std::to_string(attr));
        break;
    }
    mutex.unlock();
}

/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */


SimFPGAInterface::SimFPGAInterface(Properties* settings, SimFPGA* simFPGA) : FPGAInterface(settings) {
    this->simFPGA = simFPGA;
}

void SimFPGAInterface::init() {
    logger->info("Initializing Simulated FPGA");
    double P, I, D, Alpha;
    P = std::stod(settings->getProperty("SIM_DEPTH_P"));
    I = std::stod(settings->getProperty("SIM_DEPTH_I"));
    D = std::stod(settings->getProperty("SIM_DEPTH_D"));
    Alpha = std::stod(settings->getProperty("SIM_DEPTH_ALPHA"));
    simFPGA->set_pid_depth(P, I, D, Alpha);

    P = std::stod(settings->getProperty("SIM_YAW_P"));
    I = std::stod(settings->getProperty("SIM_YAW_I"));
    D = std::stod(settings->getProperty("SIM_YAW_D"));
    Alpha = std::stod(settings->getProperty("SIM_YAW_ALPHA"));
    simFPGA->set_pid_yaw(P, I, D, Alpha);
}

SimFPGAInterface::~SimFPGAInterface() {
    logger->info("Safely closing FPGA connection");
    delete logger;
}
