/*
 * DataTEST.cpp
 *
 *  Created on: May 12, 2015
 *      Author: ahsueh1996
 */

#include "DataTEST.h"


/* TEMPLATE
	int fail = 0;
	Logger::trace("==============================");

	if (fail > 0)
		Logger::warn("  TEST FAILED: _______");
	Logger::trace("==============================");
	return fail;
 */


int DataTEST::runUnits() {
	int res = 0;
	Logger::trace("Running all unit tests for: Data");
	Logger::trace("==============================");
	res += T_Constructor();
	res += T_setMsg();
	res += T_cpConstructor();
	res += T_opEqual();
	Logger::trace("==============================");
	if (res != 0)
		Logger::warn(StringTools::intToStr(res)+" warning(s) in unit tests");
	Logger::trace("Unit testing complete: Data");
	return res;
}

/* ==========================================================================
 * CONSTRUCTOR & DESTRUCTOR
 * ==========================================================================
 */

int DataTEST::T_Constructor() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing Constructor:");
	Logger::trace(" Constructing new Data obj with arg \"data\"...");
	Data* data = new Data("data");
	Logger::trace(" Complete.");
	Logger::trace(" Checking initialized variables...");
	Logger::trace("  Using getID()...");
	if (data->getID() == "data")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, ID initialization incorrect");
		fail += 1;
	}
	Logger::trace("  Using getMsg()...");
	if (data->getMsg() == "")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, Msg initialization incorrect");
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
	Logger::trace("==============================");

	Logger::trace("Testing setMsg():");
	Logger::trace(" Constructing new Data obj with arg \"data\"...");
	Data* data = new Data("data");
	Logger::trace(" Complete.");
	Logger::trace(" Checking initialized Msg...");
	Logger::trace("  Using getMsg()...");
	if (data->getMsg() == "")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, Msg initialization incorrect");
		fail += 1;
	}
	Logger::trace(" Setting Msg to \"hello world\"...");
	int evt = data->setMsg("hello world");
	std::string res = data->getMsg()+";error code "+StringTools::intToStr(evt);
	Logger::trace("    "+res);
	if (res == "hello world;error code 0")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, Msg set incorrect/error code incorrect");
		fail += 1;
	}
	Logger::trace(" Setting Msg to \"bye world\"...");
	evt = data->setMsg("bye world");
	res = data->getMsg()+";error code "+StringTools::intToStr(evt);
	Logger::trace("    "+res);
	if (res == "bye world;error code 1")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, Msg set incorrect/error code incorrect");
		fail += 1;
	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;

	if (fail > 0)
		Logger::warn("  TEST FAILED: setMsg()");
	Logger::trace("==============================");
	return fail;
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

int DataTEST::T_opEqual() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing operator= overload:");
	Logger::trace(" Constructing new Data obj with arg \"data\"...");
	Data* data = new Data("data");
	Logger::trace(" Set Msg to \"HII\"...");
	data->setMsg("HII");
	Logger::trace(" Assigning obj to new Data obj pointer...");
	Data* copy = data;
	Logger::trace(" Checking new obj variables...");
	Logger::trace("  Using getID()...");
	if (copy->getID() == "data")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, ID copy incorrect");
		fail += 1;
	}
	Logger::trace("  Using getMsg()...");
	if (data->getMsg() == "HII")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, Msg copy incorrect");
		fail += 1;
	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;

	if (fail > 0)
		Logger::warn("  TEST FAILED: operator= overload");
	Logger::trace("==============================");
	return fail;
}

int DataTEST::T_cpConstructor() {
	int fail = 0;
	Logger::trace("==============================");

	Logger::trace("Testing Copy Constructor:");
	Logger::trace(" Constructing new Data obj with arg \"data\"...");
	Data* data = new Data("data");
	Logger::trace(" Setting Msg to \"SubZero rox\"...");
	data->setMsg("SubZero rox");
	Logger::trace(" Invoking Copy Constructor...");
	Data* copy = new Data(*data);
	Logger::trace(" Checking variables...");
	Logger::trace("  Using getID()...");
	if (copy->getID() == "data")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, ID copy incorrect");
		fail += 1;
	}
	Logger::trace("  Using getMsg()...");
	if (copy->getMsg() == "SubZero rox")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, Msg copy incorrect");
		fail += 1;
	}
	Logger::trace(" Changing msg of copy to \"whatever\"...");
	copy->setMsg("whatever");
	Logger::trace(" Checking variables...");
	Logger::trace("  Using getMsg() on original...");
	if (data->getMsg() == "SubZero rox")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, org Msg incorrect");
		fail += 1;
	}
	Logger::trace("  Using getMsg() on copy...");
	if (copy->getMsg() == "whatever")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, copy Msg incorrect");
		fail += 1;
	}
	Logger::trace("Test complete.");
	Logger::trace("Deleting data...");
	delete data;
	delete copy;

	if (fail > 0)
		Logger::warn("  TEST FAILED: Data Copy Constructor");
	Logger::trace("==============================");
	return fail;
}
