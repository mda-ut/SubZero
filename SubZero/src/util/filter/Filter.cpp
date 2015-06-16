/*
 * Filter.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Filter.h"


Filter::Filter() {
	this->filterID = "GenericFilter";
	this->msg = "";
}

Filter::~Filter() {
}

/* ==========================================================================
 * METHODS
 * Inherent to all filters
 * ==========================================================================
 */

std::string Filter::getID() {
	return this->filterID;
}

int Filter::filter(Data* data) {
	this->track(data,this->filterID,0,0);
	return 0;
}

void Filter::setID(std::string ID) {
	this->filterID = ID;
}

std::string Filter::getMsg() {
	return this->msg;
}

int Filter::setMsg(std::string newMsg) {
	if (this->msg != "")
	{
		this->msg = newMsg;
		return 1;
	}
	this->msg = newMsg;
	return 0;
}

void Filter::track(Data* data, std::string task, int error, int type) {
	data->track(task,error,type);
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

Filter* Filter::operator =(Filter* rhs) {
	return new Filter(rhs);
}

Filter::Filter(Filter* obj) {
	this->filterID = obj->filterID;
	this->msg = obj->msg;
}

