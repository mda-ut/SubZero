/*
 * FPGAModel.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "FPGAModel.h"

FPGAModel::FPGAModel(State *inputState, HwInterface *inputInterface, double frequency)
    : Model(inputState, inputInterface, frequency) {
}

FPGAModel::~FPGAModel() {
    executing = false;
    pollThread.join();
    delete logger;
}

void FPGAModel::sendCommand(Attributes attr, int value) {
    dynamic_cast<FPGAInterface*>(interface)->set(attr, value);
}

std::vector<Data*> FPGAModel::constructDataSet(Data* rawData) {
    std::vector<Data*> fpgaDataSet;
    if (rawData != nullptr) {
        fpgaDataSet.push_back(rawData);
        for(auto& fm : filterManagerList) {
            Data* deepCopyFPGA = new FPGAData(*(dynamic_cast<FPGAData*>(rawData))); // Check if the operator overload for = is right. Don't know don't know yet
            fm->applyFilterChain(deepCopyFPGA);
            fpgaDataSet.push_back(deepCopyFPGA);
        }
    }
    return fpgaDataSet;
}

void FPGAModel::storeToState(std::vector<Data*> dataSet) {
    std::vector<FPGAData*> newData;
    for(auto& data : dataSet) {
        newData.push_back(dynamic_cast<FPGAData*>(data));
    }
    dynamic_cast<FPGAState*>(state)->setState(newData);
}

Data* FPGAModel::getStateData(std::string data_ID) {
    return state->getState(data_ID);
}
