/*
 * CameraState.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: carl
 */

#include "CameraState.h"
#include "../../util/Logger.h"
#include <iostream>

CameraState::CameraState(int stateID) : State(stateID){
	//stateData = std::list<std::vector<ImgData*> >;
}
CameraState::CameraState(int stateID, int framesStored) : State(stateID, framesStored){
}

CameraState::~CameraState(){

	//carl and zack's fix
    for(auto& vector: stateData){
		for (auto& data: vector){
			delete data;
		}
    }
    /*
	unsigned int i;
	for (i = 0; i < stateData.size(); i++){
		std::vector<ImgData*> temp = stateData.front();
		for (unsigned int n = 0; n < temp.size(); n++){
			delete temp.back();
			temp.pop_back();
		}
		stateData.pop_front();
    }*/
	//delete stateData;
}

ImgData* CameraState::getState(std::string ID){
	if (inUse){
		return 0;
	}
	inUse = true;
	std::vector<ImgData*> temp = this->stateData.back();

	for (unsigned int i = 0; i < temp.size(); i++){
		ImgData* data = temp.at(i);
		if (data->getID().compare(ID) == 0){
            ImgData *t = new ImgData(*data);		//deep copy
			inUse = false;
			return t;
		}
	}
	return 0;
}

ImgData* CameraState::getState(std::string ID, int i){
	if (inUse){
		return 0;
	}
	inUse = true;

	if (i >= (int)stateData.size()){
		return 0;				//index out of range
	}

	std::list<std::vector<ImgData*> >::reverse_iterator it = stateData.rbegin();
	std::advance(it, i);		//advance the list to the ith position

	unsigned int n = 0;
	for (n = 0; n < it->size(); n++){
		ImgData* data = it->at(n);
		if (data->getID().compare(ID) == 0){
            ImgData *t = new ImgData(*data);		//deep copy of the image
			inUse = false;
			return t;
		}
	}
	return 0;
}

int CameraState::setState(std::vector<ImgData*> d){
	if (inUse){
		return 1;
	}
	inUse = true;

	if ((int)this->stateData.size() > this->maxLength){
		std::vector<ImgData*> temp = this->stateData.front();	//delete oldest pointers
		for (unsigned int i= 0; i < temp.size(); i++){
			delete temp.at(i);
		}
		this->stateData.pop_front();
	}

	this->stateData.push_back(d);	//insert vector into list
	inUse = false;
	return 0;
}

ImgData* CameraState::getRaw(){
	return this->getState("RAW");
}

ImgData* CameraState::getRaw(int i){
	return this->getState("RAW", i);
}
