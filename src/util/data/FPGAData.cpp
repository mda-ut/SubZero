/*
 * FPGAData.cpp
 *
 *  Created on: Mar 29, 2015
 *      Author: ahsueh1996
 */

#include "FPGAData.h"

/* ==========================================================================
 * CONSTRUCTOR & DESTRUCTOR
 * ==========================================================================
 */

FPGAData::FPGAData(std::string dataID, int power, int yaw, int depth) : Data(dataID) {
    this->power = power;
    this->yaw = yaw;
    this->depth = depth;
}

FPGAData::~FPGAData() {
}


/* ==========================================================================
 * FPGA MANIPULATION FUNCS
 * ==========================================================================
 */

int FPGAData::getPower() {
    return power;
}

int FPGAData::getYaw() {
    return yaw;
}

int FPGAData::getDepth() {
    return depth;
}
