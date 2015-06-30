/*
 * FPGADataTEST.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: ahsueh1996
 */

#include "FPGADataTEST.h"

/* TEMPLATE
	int fail = 0;
	Logger::trace("==============================");

	if (fail > 0)
		Logger::warn("  TEST FAILED: _______");
	Logger::trace("==============================");
	return fail;
 */

int FPGADataTEST::runUnits() {
	int res = 0;
	Logger::trace("Running all unit tests for: FPGAData");
	Logger::trace("==============================");

//	libusb_init(0);
//	std::system("gedit test.c");
	res += T_Constructor();
//	res += T_cpConstructor();
//	res += T_opEqual();

	Logger::trace("==============================");
	if (res != 0)
		Logger::warn(StringTools::intToStr(res)+" warning(s) in unit tests");
	Logger::trace("Unit testing complete: FPGAData");
	Logger::trace("NOTE: all units mem tested");
	return res;

}

int FPGADataTEST::T_Constructor() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing Constructor:");
	Logger::trace(" Constructing new FPGAData with arg \"data\", 10.0,3.5,120...");
	FPGAData* data = new FPGAData("data",10.0,3.5,120);
	Logger::trace(" Complete.");
	Logger::trace(" Checking initialized variables...");
	Logger::trace("  Using gets()...");
	if (data->getDepth() == 10.0 && data->getSpeed() == 3.5 && data->getHeading() == 120.0)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, value initialization incorrect");
		fail += 1;
	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;

	if (fail > 0)
		Logger::warn("  TEST FAILED: Data Constructor");
	Logger::trace("==============================");
	return fail;
}

int FPGADataTEST::T_opEqual() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing Operator=:");
	Logger::trace(" Constructing new FPGAData with arg \"data\", 10.0,3.5,120...");
    FPGAData data("data",10.0,3.5,120);
	Logger::trace("  Complete.");
	Logger::trace(" Set \"copy\" equal \"data\"...");
    FPGAData copy = data;
	Logger::trace("  Complete.");
	Logger::trace(" Checking \"copy\" variables...");
	Logger::trace("  Using getID()...");
    if (copy.getID() == "data")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, ID incorrect");
		fail += 1;
	}
	Logger::trace("  Using gets()...");
    if (copy.getDepth() == 10.0 && copy.getSpeed() == 3.5 && copy.getHeading() == 120.0)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, value incorrect");
		fail += 1;
	}
	Logger::trace("Test complete.");

	if (fail > 0)
		Logger::warn("  TEST FAILED: Operator=");
	Logger::trace("==============================");
	return fail;

}

int FPGADataTEST::T_cpConstructor() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	Logger::trace("Testing Copy Constructor:");
	Logger::trace(" Constructing new FPGAData with arg \"data\", 10.0,3.5,120...");
	FPGAData* data = new FPGAData("data",10.0,3.5,120);
	Logger::trace("  Complete.");
	Logger::trace(" Constructing \"copy\" with \"data\" as arg...");
    FPGAData* copy = new FPGAData(*data);
	Logger::trace("  Complete.");
	Logger::trace(" Checking \"copy\" variables...");
	Logger::trace("  Using getID()...");
	if (copy->getID() == "data")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, ID incorrect");
		fail += 1;
	}
	Logger::trace("  Using gets()...");
	if (copy->getDepth() == 10.0 && copy->getSpeed() == 3.5 && copy->getHeading() == 120.0)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, value incorrect");
		fail += 1;
	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;
	delete copy;

	if (fail > 0)
		Logger::warn("  TEST FAILED: Copy Constructor");
	Logger::trace("==============================");
	return fail;
}
