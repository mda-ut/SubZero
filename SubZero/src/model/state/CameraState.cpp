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
	delete stateData;
}

ImgData* CameraState::getState(std::string ID){
	std::vector<ImgData*> temp = this->stateData.back();

	for (ImgData* data: temp){
		if (data->getID().compare(ID) == 0){
			return data;		//need to make a deep copy then return it
		}
	}

	return 0;
}

ImgData* CameraState::getState(std::string ID, int i){
	if (i > stateData.size()){
		return 0;				//index out of range
	}

	std::list<std::vector<ImgData*> >::reverse_iterator it = stateData.rbegin();
	std::advance(it, i);		//advance the list to the ith position

	for (ImgData* data: *it){
		if (data->getID().compare(ID) == 0){
			return data;	//return deep copy
		}
	}
	return 0;
}

int CameraState::setState(std::vector<ImgData*> d){
	this->stateData.push_back(d);	//insert vector into list
	return 0;
}

ImgData* CameraState::getRaw(){
	return this->getState("RAW");
}

ImgData* CameraState::getRaw(int i){
	return this->getState("RAW", i);
}
