/*
 * DataTEST.cpp
 *
 *  Created on: May 12, 2015
 *      Author: ahsueh1996
 */

#include "DataTEST.h"


/* TEMPLATE
	int fail = 0;
    logger->trace("==============================");

	if (fail > 0)
        logger->warn("  TEST FAILED: _______");
    logger->trace("==============================");
	return fail;
 */


int DataTEST::runUnits() {
    int res = 0;
    logger->trace("Running all unit tests for: Data");
    logger->trace("==============================");

	res += T_Constructor();
	res += T_setMsg();
//	res += T_cpConstructor();
//	res += T_opEqual();

    logger->trace("==============================");
	if (res != 0)
        logger->warn(StringTools::intToStr(res)+" warning(s) in unit tests");
    logger->trace("Unit testing complete: Data");
    logger->trace("NOTE: all units mem tested");
	return res;
}

/* ==========================================================================
 * CONSTRUCTOR & DESTRUCTOR
 * ==========================================================================
 */

int DataTEST::T_Constructor() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing Constructor:");
    logger->trace(" Constructing new Data obj with arg \"data\"...");
	Data* data = new Data("data");
    logger->trace(" Complete.");
    logger->trace(" Checking initialized variables...");
    logger->trace("  Using getID()...");
	if (data->getID() == "data")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, ID initialization incorrect");
		fail += 1;
	}
    logger->trace("  Using getMsg()...");
	if (data->getMsg() == "")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, Msg initialization incorrect");
		fail += 1;
	}
    logger->trace("Test complete.");
    logger->trace("Deleting data...");
	delete data;

	if (fail > 0)
        logger->warn("  TEST FAILED: Data Constructor");
    logger->trace("==============================");
	return fail;
}

//int DataTEST::T_Destructor() {
//}

/* ==========================================================================
 * PUBLIC FUNCS COMMON TO ALL CHILDREN
 * ==========================================================================
 */

//int DataTEST::T_getID() {
//}
//
//int DataTEST::T_getMsg() {
//}

int DataTEST::T_setMsg() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing setMsg():");
    logger->trace(" Constructing new Data obj with arg \"data\"...");
	Data* data = new Data("data");
    logger->trace(" Complete.");
    logger->trace(" Checking initialized Msg...");
    logger->trace("  Using getMsg()...");
	if (data->getMsg() == "")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, Msg initialization incorrect");
		fail += 1;
	}
    logger->trace(" Setting Msg to \"hello world\"...");
	int evt = data->setMsg("hello world");
	std::string res = data->getMsg()+";error code "+StringTools::intToStr(evt);
    logger->trace("    "+res);
	if (res == "hello world;error code 0")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, Msg set incorrect/error code incorrect");
		fail += 1;
	}
    logger->trace(" Setting Msg to \"bye world\"...");
	evt = data->setMsg("bye world");
	res = data->getMsg()+";error code "+StringTools::intToStr(evt);
    logger->trace("    "+res);
	if (res == "bye world;error code 1")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, Msg set incorrect/error code incorrect");
		fail += 1;
	}
    logger->trace("Test complete.");
    logger->trace("Deleting data...");
	delete data;

	if (fail > 0)
        logger->warn("  TEST FAILED: setMsg()");
    logger->trace("==============================");
	return fail;
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

int DataTEST::T_opEqual() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing operator= overload:");
    logger->trace(" Constructing new Data obj with arg \"data\"...");
	Data* data = new Data("data");
    logger->trace(" Set Msg to \"HII\"...");
	data->setMsg("HII");
    logger->trace(" Assigning obj to new Data obj pointer...");
	Data* copy = data;
    logger->trace(" Checking new obj variables...");
    logger->trace("  Using getID()...");
	if (copy->getID() == "data")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, ID copy incorrect");
		fail += 1;
	}
    logger->trace("  Using getMsg()...");
	if (data->getMsg() == "HII")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, Msg copy incorrect");
		fail += 1;
	}
    logger->trace("Test complete.");
    logger->trace("Deleting data...");
	delete data;

	if (fail > 0)
        logger->warn("  TEST FAILED: operator= overload");
    logger->trace("==============================");
	return fail;
}

int DataTEST::T_cpConstructor() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing Copy Constructor:");
    logger->trace(" Constructing new Data obj with arg \"data\"...");
	Data* data = new Data("data");
    logger->trace(" Setting Msg to \"SubZero rox\"...");
	data->setMsg("SubZero rox");
    logger->trace(" Invoking Copy Constructor...");
	Data* copy = new Data(*data);
    logger->trace(" Checking variables...");
    logger->trace("  Using getID()...");
	if (copy->getID() == "data")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, ID copy incorrect");
		fail += 1;
	}
    logger->trace("  Using getMsg()...");
	if (copy->getMsg() == "SubZero rox")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, Msg copy incorrect");
		fail += 1;
	}
    logger->trace(" Changing msg of copy to \"whatever\"...");
	copy->setMsg("whatever");
    logger->trace(" Checking variables...");
    logger->trace("  Using getMsg() on original...");
	if (data->getMsg() == "SubZero rox")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, org Msg incorrect");
		fail += 1;
	}
    logger->trace("  Using getMsg() on copy...");
	if (copy->getMsg() == "whatever")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, copy Msg incorrect");
		fail += 1;
	}
    logger->trace("Test complete.");
    logger->trace("Deleting data...");
	delete data;
	delete copy;

	if (fail > 0)
        logger->warn("  TEST FAILED: Data Copy Constructor");
    logger->trace("==============================");
	return fail;
}
