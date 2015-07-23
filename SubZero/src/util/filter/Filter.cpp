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
    delete logger;
}

/* ==========================================================================
 * METHODS
 * Inherent to all filters
 * ==========================================================================
 */

std::string Filter::getID() {
    return filterID;
}

bool Filter::filter(Data* data) {
    track(data, filterID, 0, 0);
    return true;
}

void Filter::setID(std::string ID) {
    filterID = ID;
}

std::string Filter::getMsg() {
    return msg;
}

int Filter::setMsg(std::string newMsg) {
    if (msg != "") {
        msg = newMsg;
        return 1;
    }
    msg = newMsg;
    return 0;
}

void Filter::track(Data* data, std::string task, int error, int type) {
    data->track(task, error, type);
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */
/*
Filter* Filter::operator =(Filter* rhs) {
    return new Filter(rhs);
}

Filter::Filter(Filter* obj) {
    this->filterID = obj->filterID;
    this->msg = obj->msg;
}
*/
