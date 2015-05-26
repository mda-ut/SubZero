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

FPGAState::~FPGAState(){
	delete stateData;
}

FPGAData* FPGAState::getState(std::string ID){
	if (inUse){
		return 0;
	}
	inUse = true;

	std::vector<FPGAData*> temp = this->stateData.back();

	for (FPGAData* data: temp){
		if (data->getID().compare(ID) == 0){
			FPGAData *t = new FPGAData(data);
			inUse = false;
			return t;
		}
	}

	return 0;
}

FPGAData* FPGAState::getState(std::string ID, int i){
	if (inUse){
		return 0;
	}
	inUse = true;

	if (i > stateData.size()){
		return 0;				//index out of range
	}

	std::list<std::vector<FPGAData*> >::reverse_iterator it = stateData.rbegin();
	std::advance(it, i);		//advance the list to the ith position

	for (FPGAData* data: *it){
		if (data->getID().compare(ID) == 0){
			FPGAData *t = new FPGAData(data);
			inUse = false;
			return t;
		}
	}
	return 0;
}

int FPGAState::setState(std::vector<FPGAData*> d){
	if (inUse){
		return 1;
	}
	inUse = true;

	if (this->stateData.size() > this->maxLength){
		this->stateData.pop_front();
	}
	this->stateData.push_back(d);
	inUse = false;
	return 0;
}

FPGAData* FPGAState::getRaw(){
	return this->getState("RAW");
}

FPGAData* FPGAState::getRaw(int i){
	return this->getState("RAW", i);
}
