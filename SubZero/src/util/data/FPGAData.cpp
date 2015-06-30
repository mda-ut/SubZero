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

FPGAData::FPGAData(std::string dataID, double depth, double speed, double heading) : Data(dataID) {
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

void FPGAData::setDepth(double newDepth) {
	this->depth = newDepth;
}

void FPGAData::setSpeed(double newSpeed) {
	this->speed = newSpeed;
}

void FPGAData::setHeading(double newHeading) {
	this->heading = newHeading;
}

/* ==========================================================================
 * FPGA MANIPULATION FUNCS
 * ==========================================================================
 */

double FPGAData::getDepth() {
	return this->depth;
}

double FPGAData::getSpeed() {
	return this->speed;
}

double FPGAData::getHeading() {
	return this->heading;
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */
/*
FPGAData FPGAData::operator=(FPGAData rhs) {
	return new FPGAData(rhs);
}

FPGAData::FPGAData(const FPGAData obj) : Data(obj) {
	this->depth = obj->depth;
	this->speed = obj->speed;
	this->heading = obj->heading;
}
*/
