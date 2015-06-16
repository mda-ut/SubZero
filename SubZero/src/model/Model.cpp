/*
 * Model.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Model.h"


/* ========================================================================== *
				protected functions
 * ========================================================================== */

FilterManager* Model::createFM(std::string fmID, int fmType){
	FilterManager* newFM = new FilterManager(fmID, fmType);
	return newFM;
}

void Model::storeToFMList(FilterManager* newFM){
	this->filterManagerList.push_back(newFM);
}

void Model::notifyObserver(){
	this->state->notifyObservers();
}


/* ========================================================================== *
				public functions
 * ========================================================================== */

Model::Model(Observable* inputObservable, HwInterface* inputHwInterface){
	this->state = inputObservable;
	this->interface = inputHwInterface;
	this->modelType = CAMERAMODEL; // Default model type is set to camera model.
}

Model::~Model(){}


/* -------------------------------------------------------------------------- *
				Filter/Filter Chain Management
 * -------------------------------------------------------------------------- */

int Model::insertFilter(std::string fmID, Filter* newFilter, std::string newFilterID){
	FilterManager* desiredFM = this->getFM(fmID);
	return desiredFM->insertFilter(newFilterID, newFilter);
}

int Model::insertFilter(std::string fmID, Filter* newFilter, std::string newFilterID, std::string targetID){
	FilterManager* desiredFM = this->getFM(fmID);
	return desiredFM->insertFilter(newFilterID, newFilter, targetID);
}

int Model::replaceFilter(std::string fmID, Filter* newFilter, std::string newFilterID, std::string targetID){
	FilterManager* desiredFM = this->getFM(fmID);
	return desiredFM->replaceFilter(newFilterID, newFilter, targetID);
}

int Model::deleteFilter(std::string fmID, std::string targetID){
	FilterManager* desiredFM = this->getFM(fmID);
	return desiredFM->deleteFilter(targetID);
}

void Model::deleteFilterChain(std::string fmID){
	FilterManager* desiredFM = this->getFM(fmID);
	return desiredFM->deleteFilterChain();
}

int Model::getFilterChainSize(std::string fmID){
	FilterManager* desiredFM = this->getFM(fmID);
	return desiredFM->getSizeOfFilterChain();
}

std::vector<std::string> Model::getFilterChainIDs(std::string fmID){
	FilterManager* desiredFM = this->getFM(fmID);
	return desiredFM->getFilterChainIDs();
}


/* -------------------------------------------------------------------------- *
				Filter Manager / Filter Manager List Management
 * -------------------------------------------------------------------------- */

std::vector<std::string> Model::getFMListIDs(){
	std::vector<std::string> fmListIDs;
	for(std::vector<FilterManager*>::iterator it = filterManagerList.begin();it!=filterManagerList.end();++it){
		std::string currentFMID = (*it)->getFMID();
		fmListIDs.push_back(currentFMID);
	}
	return fmListIDs;
}

void Model::createAndStoreFM(std::string fmID, int fmType){
	FilterManager* newFM = this->createFM(fmID, fmType);
	this->storeToFMList(newFM);
}

void Model::deleteFM(std::string fmID){
	for(std::vector<FilterManager*>::iterator it = filterManagerList.begin();it!=filterManagerList.end();++it){
		if((*it)->getFMID() == fmID){
			filterManagerList.erase(it);
		}
	}
}

void Model::deleteFMList(){
	this->filterManagerList.erase(filterManagerList.begin(),filterManagerList.end());
}

FilterManager* Model::getFM(std::string fmID){
	for(std::vector<FilterManager*>::iterator it = filterManagerList.begin();it!=filterManagerList.end();++it){
		if((*it)->getFMID() == fmID){
			return (*it);
		}
	}
	return nullptr;
}
