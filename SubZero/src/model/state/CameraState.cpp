/*
 * CameraState.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: carl
 */

#include "CameraState.h"
#include "../../util/Logger.h"
#include <iostream>

CameraState::CameraState(int stateID) : State(stateID) {

}
CameraState::CameraState(int stateID, int framesStored) : State(stateID, framesStored) {

}

CameraState::~CameraState(){

    //carl and zack's fix
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

ImgData* CameraState::getState(std::string id, int i) {
    if (i >= (int)stateData.size() || i < 0) {
        logger->debug("Specified index '" + std::to_string(i) + "' is out of bounds");
        return 0;
    }

    std::list<std::vector<ImgData*> >::reverse_iterator it = stateData.rbegin();
    std::advance(it, i);		//advance the list to the ith position


    unsigned int n = 0;
    for (n = 0; n < it->size(); n++) {
        ImgData* data = it->at(n);
        if (data->getID().compare(id) == 0) {
            ImgData *t = new ImgData(*data);
            inUse = false;
            logger->info("State '" + id + "' found");
            return t;
        }
    }

    logger->info("State '" + id + "' was not found");
    return 0;
}

int CameraState::setState(std::vector<ImgData*> d) {
    if ((int)this->stateData.size() > this->maxLength){
        std::vector<ImgData*> temp = this->stateData.front();	//delete oldest pointers
        for (unsigned int i= 0; i < temp.size(); i++){
            delete temp[i];
        }
        this->stateData.pop_front();
    }

    this->stateData.push_back(d);	//insert vector into list
    return 0;
}

ImgData* CameraState::getRaw() {
    return this->getState("RAW");
}

ImgData* CameraState::getRaw(int i) {
    return this->getState("RAW", i);
}
