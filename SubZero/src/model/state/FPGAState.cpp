/*
 * FPGAState.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: carl
 */

#include "FPGAState.h"


FPGAState::FPGAState() : State(){
}
FPGAState::FPGAState(int framesStored) : State(framesStored){
}

FPGAState::~FPGAState() : ~State(){
}

FPGAData* FPGAState::getState(std::string ID){
	return (FPGAData*)State::getState(ID);
}

FPGAData* FPGAState::getState(std::string ID, int i){
	return (FPGAData*)State::getState(ID, i);
}

int FPGAState::setState(std::vector<FPGAData*> d){
	this->stateData.push_back(d);	//insert vector into list
	return 0;
}

FPGAData* FPGAState::getRaw(){
	return (FPGAData*) State::getRaw();
}

FPGAData* FPGAState::getRaw(int i){
	return (FPGAData*) State::getRaw(i);
}
