/*
 * CameraState.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: carl
 */

#include "CameraState.h"

CameraState::CameraState() : State(){
}
CameraState::CameraState(int framesStored) : State(framesStored){
}

CameraState::~CameraState() : ~State(){
}

ImgData* CameraState::getState(std::string ID){
	return (ImgData*)getState(ID);
}

ImgData* CameraState::getState(std::string ID, int i){
	return (ImgData*)getState(ID, i);
}

int CameraState::setState(std::vector<ImgData*> d){
	State::setState(d);
	return setState(d);
}
