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

void FPGAModel::sendCommand(std::string cmd) {
// Emma go!!
}

Data* FPGAModel::getDataFromBuffer() {
    Data* rawFPGAData = interface->getDataFromBuffer<FPGAData>();
    return rawFPGAData;
}

std::vector<Data*> FPGAModel::constructDataSet() {
    std::vector<Data*> fpgaDataSet;
    //Data* rawFPGAData = this->getDataFromBuffer();
    Data* rawFPGAData = interface->getDataFromBuffer<FPGAData>();
    fpgaDataSet.push_back(rawFPGAData);
    for(auto& fm : filterManagerList){
        Data* deepCopyFPGA = new FPGAData(*((FPGAData*)rawFPGAData)); // Check if the operator overload for = is right. Don't know don't know yet
        fm->applyFilterChain(deepCopyFPGA);
        fpgaDataSet.push_back(deepCopyFPGA);
    }
    return fpgaDataSet;
}

void FPGAModel::storeToState(std::vector<Data*> dataSet) {
    std::vector<FPGAData*> newData;
    for(std::vector<Data*>::iterator it = dataSet.begin(); it != dataSet.end(); ++it){
        newData.push_back((FPGAData*)(*it));
    }
    ((FPGAState*) &(this->state))->setState(newData);
}

bool FPGAModel::dataTransfer() {
    storeToState(constructDataSet());
    return true;
}
