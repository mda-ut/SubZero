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

FilterManager* Model::createFM(std::string fmID, int fmType) {
    FilterManager* newFM = new FilterManager(fmID, fmType);
    logger->info("Filter Manager " + fmID + " created");
    return newFM;
}

void Model::storeToFMList(FilterManager* newFM) {
    filterManagerList.push_back(newFM);
    logger->info("Filter Manager " + newFM->getFMID() + " added");
}

void Model::notifyObserver() {
    state->notifyViewers();
}


/* ========================================================================== *
                public functions
 * ========================================================================== */

Model::Model(State* inputState, HwInterface* inputHwInterface) {
    state = inputState;
    interface = inputHwInterface;
}

Model::~Model() {
    delete state;
    delete interface;
    for (auto& fm : filterManagerList) {
        delete fm;
    }

    delete logger;
}

void Model::initialize() {
    interface->init();
}

State *Model::getState() {
    return state;
}

/* -------------------------------------------------------------------------- *
                Filter/Filter Chain Management
 * -------------------------------------------------------------------------- */

int Model::insertFilter(std::string fmID, Filter* newFilter, std::string newFilterID) {
    int returnCode = 0;
    FilterManager* desiredFM = getFM(fmID);
    if (desiredFM == nullptr) {
        return 3;	//TODO: Fix return code
    }
    returnCode = desiredFM->insertFilter(newFilterID, newFilter);
    return returnCode;
}

int Model::insertFilter(std::string fmID, Filter* newFilter, std::string newFilterID, std::string targetID) {
    FilterManager* desiredFM = getFM(fmID);
    return desiredFM->insertFilter(newFilterID, newFilter, targetID);
}

int Model::replaceFilter(std::string fmID, Filter* newFilter, std::string newFilterID, std::string targetID) {
    FilterManager* desiredFM = getFM(fmID);
    return desiredFM->replaceFilter(newFilterID, newFilter, targetID);
}

int Model::deleteFilter(std::string fmID, std::string targetID) {
    FilterManager* desiredFM = getFM(fmID);
    return desiredFM->deleteFilter(targetID);
}

void Model::deleteFilterChain(std::string fmID) {
    FilterManager* desiredFM = getFM(fmID);
    return desiredFM->deleteFilterChain();
}

int Model::getFilterChainSize(std::string fmID) {
    FilterManager* desiredFM = getFM(fmID);
    return desiredFM->getSizeOfFilterChain();
}

std::vector<std::string> Model::getFilterChainIDs(std::string fmID) {
    FilterManager* desiredFM = getFM(fmID);
    return desiredFM->getFilterChainIDs();
}


/* -------------------------------------------------------------------------- *
                Filter Manager / Filter Manager List Management
 * -------------------------------------------------------------------------- */

std::vector<std::string> Model::getFMListIDs() {
    std::vector<std::string> fmListIDs;
    for(std::vector<FilterManager*>::iterator it = filterManagerList.begin() ; it != filterManagerList.end(); ++it) {
        std::string currentFMID = (*it)->getFMID();
        fmListIDs.push_back(currentFMID);
    }
    return fmListIDs;
}

void Model::createAndStoreFM(std::string fmID, int fmType) {
    FilterManager* newFM = createFM(fmID, fmType);
    storeToFMList(newFM);
}

void Model::deleteFM(std::string fmID) {
    for(std::vector<FilterManager*>::iterator it = filterManagerList.begin(); it != filterManagerList.end(); ++it) {
        if((*it)->getFMID() == fmID) {
            filterManagerList.erase(it);
            logger->info("Filter Manager with ID " + fmID + " removed");
        }
    }
    logger->debug("Filter Manager with ID " + fmID + " not found");
}

void Model::deleteFMList() {
    filterManagerList.erase(filterManagerList.begin(), filterManagerList.end());
    logger->info("Filter Managers removed");
}

FilterManager* Model::getFM(std::string fmID) {
    for(std::vector<FilterManager*>::iterator it = filterManagerList.begin(); it != filterManagerList.end(); ++it) {
        if((*it)->getFMID() == fmID) {
            return (*it);
        }
    }
    logger->warn("Filter Manager with ID " + fmID + " not found");
    return nullptr;
}
