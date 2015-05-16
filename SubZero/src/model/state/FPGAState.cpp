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
	std::vector<FPGAData*> temp = this->stateData.back();

	for (FPGAData* data: temp){
		if (data->getID().compare(ID) == 0){
			return data;		//need to make a deep copy then return it
		}
	}

	return 0;
}

FPGAData* FPGAState::getState(std::string ID, int i){
	if (i > stateData.size()){
		return 0;				//index out of range
	}

	std::list<std::vector<FPGAData*> >::reverse_iterator it = stateData.rbegin();
	std::advance(it, i);		//advance the list to the ith position

	for (FPGAData* data: *it){
		if (data->getID().compare(ID) == 0){
			return data;	//return deep copy
		}
	}
	return 0;
}

int FPGAState::setState(std::vector<FPGAData*> d){
	this->stateData.push_back(d);	//insert vector into list
	return 0;
}

FPGAData* FPGAState::getRaw(){
	return this->getState("RAW");
}

FPGAData* FPGAState::getRaw(int i){
	return this->getState("RAW", i);
}
