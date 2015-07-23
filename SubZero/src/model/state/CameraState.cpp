/*
 * CameraState.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: carl
 */

#include "CameraState.h"
#include "../../util/Logger.h"
#include <iostream>
#include <QMutexLocker>

CameraState::CameraState(int stateID, uint32_t bufferSize) : State(stateID, bufferSize) {
}

CameraState::~CameraState(){
    for(auto& vector: stateData){
        for (auto& data: vector){
            delete data;
        }
    }

    delete logger;
}

ImgData* CameraState::getState(std::string id) {
    return getState(id, 0);
}

ImgData* CameraState::getState(std::string id, uint32_t i) {
    QMutexLocker locker(&mutex);

    if (i >= stateData.size()) {
        logger->debug("Specified index '" + std::to_string(i) + "' is out of bounds");
        return 0;
    }

    std::list<std::vector<ImgData*> >::reverse_iterator it = stateData.rbegin();
    std::advance(it, i);		//advance the list to the ith position

    for (auto& data : *it) {
        if (data->getID().compare(id) == 0) {
            ImgData *t = data; //shallow copy quick fix
            return t;
        }
    }
    logger->info("State '" + id + "' was not found");
    return 0;
}

ImgData* CameraState::getDeepState(std::string id){
    return getDeepState(id, 0);
}

ImgData* CameraState::getDeepState(std::string id, uint32_t i){
    QMutexLocker locker(&mutex);

    if (i >= stateData.size()) {
        logger->debug("Specified index '" + std::to_string(i) + "' is out of bounds");
        return 0;
    }

    std::list<std::vector<ImgData*> >::reverse_iterator it = stateData.rbegin();
    std::advance(it, i);		//advance the list to the ith position

    for (auto& data : *it) {
        if (data->getID().compare(id) == 0) {
            ImgData *t = new ImgData(*data); //deep copy to return
            return t;
        }
    }
    logger->info("State '" + id + "' was not found");
    return 0;
}

int CameraState::setState(std::vector<ImgData*> d) {
    QMutexLocker locker(&mutex);
    logger->trace("Setting new camera state date");
    if (this->stateData.size() > this->bufferSize){
        std::vector<ImgData*> temp = this->stateData.front();	//delete oldest pointers
        for (auto& data : temp){
            delete data;
        }
        this->stateData.pop_front();
    }

    this->stateData.push_back(d);	//insert vector into list
    locker.unlock();
    emit notifyViewers(stateID);
    return 0;
}

ImgData* CameraState::getRaw() {
    return this->getState("raw");
}

ImgData* CameraState::getRaw(uint32_t i) {
    return this->getState("raw", i);
}
