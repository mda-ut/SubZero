/*
 * CameraState.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: carl
 */

#include "CameraState.h"

CameraState::CameraState() : State(){
	//stateData = std::list<std::vector<ImgData*> >;
}
CameraState::CameraState(int framesStored) : State(framesStored){
}

CameraState::~CameraState(){
	//do i have to iterate to every pointer and delete it?
	for (auto& vector : stateData) {
		for (auto& data : vector) {
			delete data;
		}
	}
}

ImgData* CameraState::getState(std::string ID){
	if (inUse){
		return 0;
	}
	inUse = true;
	std::vector<ImgData*> temp = this->stateData.back();

	for (ImgData* data: temp){
		if (data->getID().compare(ID) == 0){
			ImgData *t = new ImgData(data);		//deep copy
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

	if (i > (int)stateData.size()){
		return 0;				//index out of range
	}

	std::list<std::vector<ImgData*> >::reverse_iterator it = stateData.rbegin();
	std::advance(it, i);		//advance the list to the ith position

	for (ImgData* data: *it){
		if (data->getID().compare(ID) == 0){
			ImgData *t = new ImgData(data);		//deep copy of the image
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
		this->stateData.pop_front();		//not sure if this will cause a memory leak
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
