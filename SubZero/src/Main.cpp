/*
 * Main.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "util/Logger.h"

int main(int argc, char** argv) {
	Logger::initialize(true, false, new Timer());
	Logger::trace("Logger initialized.");
	return 0;
}

