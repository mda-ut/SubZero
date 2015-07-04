/*
 * FPGAModel.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "FPGAModel.h"

FPGAModel::FPGAModel(State *inputState, HwInterface *inputInterface) : Model(inputState, inputInterface) {

}

FPGAModel::~FPGAModel() {
    delete logger;
}

void FPGAModel::sendCommand(Attributes attr, int value) {
    dynamic_cast<FPGAInterface*>(interface)->set(attr, value);
}

Data* FPGAModel::getDataFromBuffer() {
    Data* rawFPGAData = interface->getDataFromBuffer<FPGAData>();
    return rawFPGAData;
}

std::vector<Data*> FPGAModel::constructDataSet() {
    std::vector<Data*> fpgaDataSet;
    Data* rawFPGAData = getDataFromBuffer();
    if (rawFPGAData != nullptr) {
        fpgaDataSet.push_back(rawFPGAData);
        for(auto& fm : filterManagerList) {
            Data* deepCopyFPGA = new FPGAData(*(dynamic_cast<FPGAData*>(rawFPGAData))); // Check if the operator overload for = is right. Don't know don't know yet
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
    notifyObserver();
}

Data* FPGAModel::getState(std::string data_ID) {
    return state->getState(data_ID);
}

bool FPGAModel::dataTransfer() {
    auto fpgaDataSet = constructDataSet();
    if (!fpgaDataSet.empty()) {
        storeToState(fpgaDataSet);
        return true;
    }
    return false;
}
