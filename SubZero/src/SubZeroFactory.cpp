/*
 * SubZeroFactory.cpp
 *
 *  Created on: May 25, 2015
 *      Author: carl
 */

#include "SubZeroFactory.h"
#include <iostream>

SubZeroFactory::SubZeroFactory() {
	// TODO Auto-generated constructor stub

}

SubZeroFactory::~SubZeroFactory() {
	// TODO Auto-generated destructor stub
}

SubZero* SubZeroFactory::makeSubZero(int subType) {
	switch (subType) {
	case GUI:
		//TODO SubZero has models, which needs States, FMs, and Interfaces, which need filters? and observers? which needs View, which needs Controller, which needs Model?
		std::cout << "guisub" << std::endl;

		break;
	case SIM:
		std::cout << "simsub" << std::endl;
		break;
	case AUT:
		std::cout << "autsub" << std::endl;
		break;
	default:
		std::cout << "unrecognized sub type: " << subType << std::endl;
        break;
	}
    SubZero* sub = new SubZero();
    return sub;
}

