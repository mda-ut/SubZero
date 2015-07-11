/*
 * FPGAState.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: carl
 */

#include "FPGAState.h"

FPGAState::FPGAState(int stateID) : State(stateID) {
    logger = new Logger("FPGAState");
}
FPGAState::FPGAState(int stateID, int framesStored) : State(stateID, framesStored) {
    logger = new Logger("FPGAState");
}

FPGAState::~FPGAState() {
    for (auto& vector : stateData) {
        for (auto& data : vector) {
            delete data;
        }
    }

    logger->close();
    delete logger;
}

FPGAData* FPGAState::getState(std::string id) {
    return getState(id, 0);
}

FPGAData* FPGAState::getState(std::string id, int i) {
    if (inUse) {
        logger->info("State '" + id + "' is in use and cannot be read");
        return 0;
    }
    inUse = true;

    if (i >= (int)stateData.size() || i < 0) {
        logger->debug("Specified index '" + std::to_string(i) + "' is out of bounds");
        return 0;
    }

    std::list<std::vector<FPGAData*> >::reverse_iterator it = stateData.rbegin();
    std::advance(it, i);		//advance the list to the ith position


    unsigned int n = 0;
    for (n = 0; n < it->size(); n++) {
        FPGAData* data = it->at(n);
        if (data->getID().compare(id) == 0) {
            FPGAData *t = new FPGAData(*data);
            inUse = false;
            return t;
        }
    }

    logger->info("State '" + id + "' was not found");
    return 0;
}

int FPGAState::setState(std::vector<FPGAData*> d){
    if (inUse) {
        logger->info("State is in use and cannot be set");
        return 1;
    }
    inUse = true;

    if ((int)this->stateData.size() > this->maxLength){
        std::vector<FPGAData*> temp = this->stateData.front();
        for (unsigned int i= 0; i < temp.size(); i++){
            delete temp[i];
        }
        this->stateData.pop_front();
    }
    this->stateData.push_back(d);
    inUse = false;
    return 0;
}

FPGAData* FPGAState::getRaw() {
    return this->getState("RAW");
}

FPGAData* FPGAState::getRaw(int i) {
    return this->getState("RAW", i);
}
