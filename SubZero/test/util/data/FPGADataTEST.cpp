/*
 * FPGADataTEST.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: ahsueh1996
 */

#include "FPGADataTEST.h"

/* TEMPLATE
	int fail = 0;
    logger->trace("==============================");

	if (fail > 0)
        logger->warn("  TEST FAILED: _______");
    logger->trace("==============================");
	return fail;
 */

int FPGADataTEST::runUnits() {
	int res = 0;
    logger->trace("Running all unit tests for: FPGAData");
    logger->trace("==============================");

//	libusb_init(0);
//	std::system("gedit test.c");
	res += T_Constructor();
//	res += T_cpConstructor();
//	res += T_opEqual();

    logger->trace("==============================");
	if (res != 0)
        logger->warn(StringTools::intToStr(res)+" warning(s) in unit tests");
    logger->trace("Unit testing complete: FPGAData");
    logger->trace("NOTE: all units mem tested");
	return res;

}

int FPGADataTEST::T_Constructor() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing Constructor:");
    logger->trace(" Constructing new FPGAData with arg \"data\", 10.0,3.5,120...");
	FPGAData* data = new FPGAData("data",10.0,3.5,120);
    logger->trace(" Complete.");
    logger->trace(" Checking initialized variables...");
    logger->trace("  Using gets()...");
    /*if (data->getDepth() == 10.0 && data->getSpeed() == 3.5 && data->getHeading() == 120.0)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, value initialization incorrect");
		fail += 1;
    }*/
    logger->trace("Test complete.");
    logger->trace("Deleting data...");
	delete data;

	if (fail > 0)
        logger->warn("  TEST FAILED: Data Constructor");
    logger->trace("==============================");
	return fail;
}

int FPGADataTEST::T_opEqual() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing Operator=:");
    logger->trace(" Constructing new FPGAData with arg \"data\", 10.0,3.5,120...");
    FPGAData data("data",10.0,3.5,120);
    logger->trace("  Complete.");
    logger->trace(" Set \"copy\" equal \"data\"...");
    FPGAData copy = data;
    logger->trace("  Complete.");
    logger->trace(" Checking \"copy\" variables...");
    logger->trace("  Using getID()...");
    if (copy.getID() == "data")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, ID incorrect");
		fail += 1;
	}
    logger->trace("  Using gets()...");
    /*if (copy.getDepth() == 10.0 && copy.getSpeed() == 3.5 && copy.getHeading() == 120.0)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, value incorrect");
		fail += 1;
    }*/
    logger->trace("Test complete.");

	if (fail > 0)
        logger->warn("  TEST FAILED: Operator=");
    logger->trace("==============================");
	return fail;

}

int FPGADataTEST::T_cpConstructor() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing Copy Constructor:");
    logger->trace(" Constructing new FPGAData with arg \"data\", 10.0,3.5,120...");
	FPGAData* data = new FPGAData("data",10.0,3.5,120);
    logger->trace("  Complete.");
    logger->trace(" Constructing \"copy\" with \"data\" as arg...");
    FPGAData* copy = new FPGAData(*data);
    logger->trace("  Complete.");
    logger->trace(" Checking \"copy\" variables...");
    logger->trace("  Using getID()...");
	if (copy->getID() == "data")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, ID incorrect");
		fail += 1;
	}
    logger->trace("  Using gets()...");
    /*if (copy->getDepth() == 10.0 && copy->getSpeed() == 3.5 && copy->getHeading() == 120.0)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, value incorrect");
		fail += 1;
    }*/
    logger->trace("Test complete.");
    logger->trace("Deleting data...");
	delete data;
	delete copy;

	if (fail > 0)
        logger->warn("  TEST FAILED: Copy Constructor");
    logger->trace("==============================");
	return fail;
}
