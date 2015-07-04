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

FPGAData::FPGAData(std::string dataID, int depth, int speed, int heading) : Data(dataID) {
	this->depth = depth;
	this->speed = speed;
	this->heading = heading;
}

FPGAData::~FPGAData() {
}

/* ==========================================================================
 * FRIEND FUNCS
 * ==========================================================================
 */

void FPGAData::setDepth(int newDepth) {
    depth = newDepth;
}

void FPGAData::setSpeed(int newSpeed) {
    speed = newSpeed;
}

void FPGAData::setHeading(int newHeading) {
    heading = newHeading;
}

/* ==========================================================================
 * FPGA MANIPULATION FUNCS
 * ==========================================================================
 */

int FPGAData::getDepth() {
    return depth;
}

int FPGAData::getSpeed() {
    return speed;
}

int FPGAData::getHeading() {
    return heading;
}
