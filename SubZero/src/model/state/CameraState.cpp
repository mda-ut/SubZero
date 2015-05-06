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

CameraState::~CameraState() : ~State(){
}

ImgData* CameraState::getState(std::string ID){
	return (ImgData*)State::getState(ID);
}

ImgData* CameraState::getState(std::string ID, int i){
	return (ImgData*)State::getState(ID, i);
}

int CameraState::setState(std::vector<ImgData*> d){
	this->stateData.push_back(d);	//insert vector into list
	return 0;
}

ImgData* CameraState::getRaw(){
	return (ImgData*) State::getRaw();
}

ImgData* CameraState::getRaw(int i){
	return (ImgData*) State::getRaw(i);
}
