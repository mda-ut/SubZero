/*
 * FPGAState.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: carl
 */

#include "FPGAState.h"
#include <QMutexLocker>

FPGAState::FPGAState(int stateID, uint32_t bufferSize) : State(stateID, bufferSize) {
}

FPGAState::~FPGAState() {
    for (auto& vector : stateData) {
        for (auto& data : vector) {
            delete data;
        }
    }
    delete logger;
}

FPGAData* FPGAState::getState(std::string id) {
    return getState(id, 0);
}

FPGAData* FPGAState::getState(std::string id, uint32_t i) {
    QMutexLocker locker(&mutex);

    if (i >= stateData.size()) {
        logger->debug("Specified index '" + std::to_string(i) + "' is out of bounds");
        return 0;
    }

    std::list<std::vector<FPGAData*> >::reverse_iterator it = stateData.rbegin();
    std::advance(it, i);		//advance the list to the ith position

    //for each fpga pointer within the i'th vector
    for (auto& data : *it) {
        if (data->getID().compare(id) == 0) {
            FPGAData *t = data; //shallow copy or deep copy... currently just shallow
            return t;
        }
    }

    logger->info("State '" + id + "' was not found");
    return 0;
}

int FPGAState::setState(std::vector<FPGAData*> d){
    QMutexLocker locker(&mutex);

    if (this->stateData.size() > this->bufferSize){
        std::vector<FPGAData*> temp = this->stateData.front();
        for (auto& data : temp){
            delete data;
        }
        this->stateData.pop_front();
    }
    this->stateData.push_back(d);
    locker.unlock();
    emit notifyViewers(stateID);
    return 0;
}

FPGAData* FPGAState::getRaw() {
    return this->getState("raw");
}

FPGAData* FPGAState::getRaw(uint32_t i) {
    return this->getState("raw", i);
}
