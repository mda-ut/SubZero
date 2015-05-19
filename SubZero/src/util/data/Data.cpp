/*
 * Data.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: ahsueh1996
 */

#include "Data.h"

/* ==========================================================================
 * CONSTRUCTOR & DESTRUCTOR
 * ==========================================================================
 */

Data::Data(std::string dataID) {
	this->dataID = dataID;
	this->msg = "";
}


Data::~Data() {
}

/* ==========================================================================
 * PUBLIC FUNCS COMMON TO ALL CHILDREN
 * ==========================================================================
 */

std::string Data::getID(){
	return this->dataID;
}

std::string Data::getMsg(){
	return this->msg;
}

int Data::setMsg(std::string newMsg){
	if (this->msg != "")
	{
		this->msg = newMsg;
		return 1;
	}
	this->msg = newMsg;
	return 0;
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

Data* Data::operator=(Data* rhs) {
	return new Data(rhs);
}

Data::Data(const Data* obj) {
	this->dataID = obj->dataID;
	this->msg = obj->msg;
}
