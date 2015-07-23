/*
 * Model.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Model.h"
#include "Timer.h"


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

void Model::pollLoop() {
    Timer timer;
    timer.start();
    double pollPeriod = 1 / pollFrequency;
    while(executing) {
        double elapsedTime = timer.getTimeElapsed();
        while (elapsedTime < pollPeriod) {
            std::this_thread::yield();
            elapsedTime = timer.getTimeElapsed();
        }
        timer.start(); //restart timer
        dataTransfer();
    }
}

void Model::dataTransfer() {
    Data* new_data = interface->poll();
    std::vector<Data*> new_dataSet = constructDataSet(new_data);
    if (!new_dataSet.empty()) {
        storeToState(new_dataSet);
    } else {
        logger->info("Failed to transfer data");
    }
}


/* ========================================================================== *
                public functions
 * ========================================================================== */

Model::Model(State* inputState, HwInterface* inputHwInterface, double frequency) {
    state = inputState;
    interface = inputHwInterface;
    pollFrequency = frequency;
}

Model::~Model() {
    delete interface;
    delete state;
    for (auto& fm : filterManagerList) {
        delete fm;
    }

    delete logger;
}

void Model::initialize() {
    interface->init();
    executing = true;
    pollThread = std::thread(&Model::pollLoop, this);
    logger->info("Thread started");
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
