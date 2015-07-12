/*
 * FPGAInterface.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "FPGAInterface.h"
#include <string>
#include "scripts.h"


/* ==========================================================================
 * 				INTERACTING WITH DATA COMING IN (FROM FPGA)
 * ==========================================================================
 * This interface class will be automatically polling and managing
 * the polling process privately within the interface at pollFrequency
 * using the functions below.
 */

FPGAData* FPGAInterface::poll() {
    mutex.lock();
    //TODO Add error checking on values from FPGA
    int power = get_power();
    int depth = get_depth();
    int yaw = get_yaw();
    mutex.unlock();

    return new FPGAData("raw", power, yaw, depth);
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

/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */


FPGAInterface::FPGAInterface(Properties* settings) {
    this->settings = settings;
}

void FPGAInterface::init() {
    logger->info("Initializing FPGA connection");
    init_fpga();
    set_verbose(0);

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

}

FPGAInterface::~FPGAInterface() {
    logger->info("Safely closing FPGA connection");
    exit_safe();
    delete logger;
}
