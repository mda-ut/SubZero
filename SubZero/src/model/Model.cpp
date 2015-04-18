/*
 * Model.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Model.h"

/* Protected functions */

FilterManager* Model::createFM(std::string fmID, int fmType){
	FilterManager* newFilterManager = new FilterManager(fmID,fmType);
	return newFilterManager;
}

void Model::storeToFMList(FilterManager* newFM){
	this->filterManagerList.push_back(newFM);
}


/* Public functions */

Model::Model(Observable* inputObservable, HwInterface* inputHwInterface)
{
	this->state = inputObservable;
	this->interface = inputHwInterface;
	this->modelType = CAMERAMODEL; // Initialize modelType to CAMERAMODEL;
}

Model::~Model()
{
	// TODO Auto-generated destructor stub
}

/* ********** ********** ********** ********** ********** */
/* HwInterface related */

int Model::sendCommand(std::string newCommand){
	return 0;
} // not completed

/* ********** ********** ********** ********** ********** */
/* Observable/State related */

void Model::notifyObserver(){
	this->state->notifyObservers();
}

/* ********** ********** ********** ********** ********** */
/* FilterManager related */

int Model::insertFilter(std::string fmID, Filter* newFilter, std::string newFilterID){
	FilterManager* currentFM = getFM(fmID);
	return currentFM -> insertFilter(newFilterID, newFilter);
}

int Model::insertFilter(std::string fmID, Filter* newFilter, std::string newFilterID, std::string targetID){
	FilterManager* currentFM = getFM(fmID);
	return currentFM -> insertFilter(newFilterID, newFilter, targetID);
}

int Model::replaceFilter(std::string fmID, Filter* newFilter, std::string newFilterID, std::string targetID){
	FilterManager* currentFM = getFM(fmID);
	return currentFM -> replaceFilter(newFilterID, newFilter, targetID);
}

int Model::deleteFilter(std::string fmID, std::string targetID){
	FilterManager* currentFM = getFM(fmID);
	return currentFM -> deleteFilter(targetID);
}

int Model::deleteFilterChain(std::string fmID){
	FilterManager* currentFM = getFM(fmID);
	return currentFM -> deleteFilterChain();
}

int Model::getFilterChainSize(std::string fmID){
	FilterManager* currentFM = getFM(fmID);
	return currentFM -> getSizeOfFilter();
}

std::vector<std::string> Model::getFilterChainIDs(std::string fmID){
	FilterManager* currentFM = getFM(fmID);
	return currentFM -> getFilterChainIDs();
}

std::vector<std::string> Model::getFMListIDs(){
	std::vector<std::string> fmListIDs;
	for (std::vector<FilterManager*>::iterator it = filterManagerList.begin(); it != filterManagerList.end(); ++it)
		fmListIDs.push_back ((*it) -> getFMID());
	return fmListIDs;
}

void Model::createAndAddToFMList(std::string fmID, int fmType){
	storeToFMList(createFM(std::string fmID, int fmType));
}

int Model::deleteFM(std::string fmID){
	if (fmID.compare("ALL") == 0)
		this->filterManagerList.clear();
	else {
		for (std::vector<FilterManager*>::iterator it = filterManagerList.begin(); it != filterManagerList.end(); ++it){
			if (((*it) -> getFMID()).compare(fmID) == 0){
				filterManagerList.erase(it);
				break;
			}
		}
	}
	return 0;
}

FilterManager* Model::getFM(std::string fmID){
	FilterManager* returnThisFM = nullptr;
	for (std::vector<FilterManager*>::iterator it = filterManagerList.begin(); it != filterManagerList.end(); ++it){
		if (((*it) -> getFMID()).compare(fmID) == 0){
			returnThisFM = *it;
			break;
		}
	}
	return returnThisFM;
}
