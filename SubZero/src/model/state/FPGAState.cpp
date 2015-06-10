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
	unsigned int i;
	for (i = 0; i < stateData.size(); i++){
		std::vector<FPGAData*> temp = stateData.front();
		for (unsigned int n = 0; n < temp.size(); n++){
			delete temp.back();
			temp.pop_back();
		}
		stateData.pop_front();
	}
	//delete stateData;
}

FPGAData* FPGAState::getState(std::string ID){
	if (inUse){
		return 0;
	}
	inUse = true;

	std::vector<FPGAData*> temp = this->stateData.back();

	unsigned int i;
	for (i = 0; i < temp.size(); i++){
		FPGAData* data = temp.at(i);
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

	if (i >= (int)stateData.size()){
		return 0;				//index out of range
	}

	std::list<std::vector<FPGAData*> >::reverse_iterator it = stateData.rbegin();
	std::advance(it, i);		//advance the list to the ith position


	unsigned int n = 0;
	for (n = 0; n < it->size(); n++){
		FPGAData* data = it->at(n);
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

	if ((int)this->stateData.size() > this->maxLength){
		std::vector<FPGAData*> temp = this->stateData.front();
		for (unsigned int i= 0; i < temp.size(); i++){
			delete temp.at(i);
		}
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
