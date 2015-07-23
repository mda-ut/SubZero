/*
 * CameraModel.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "CameraModel.h"

CameraModel::CameraModel(State*inputState, HwInterface *inputInterface, double frequency)
    : Model(inputState, inputInterface, frequency) {
}

CameraModel::~CameraModel() {
    executing = false;
    pollThread.join();
    delete logger;
}

void CameraModel::sendCommand(Attributes attr, int value) {
    logger->warn("Camera has no commands to send");
}

std::vector<Data*> CameraModel::constructDataSet(Data* rawData) {
    std::vector<Data*> imageDataSet;
    if (rawData != nullptr) {
        imageDataSet.push_back(rawData);
        for(auto& fm : filterManagerList) {
            Data* deepCopyImage = new ImgData(*(dynamic_cast<ImgData*>(rawData))); // Check if the operator overload for = is right. Don't know yet
            fm->applyFilterChain(deepCopyImage);
            imageDataSet.push_back(deepCopyImage);
        }
    }
    return imageDataSet;
}

void CameraModel::storeToState(std::vector<Data*> dataSet) {
    std::vector<ImgData*> newData;
    for(auto& data : dataSet) {
        newData.push_back(dynamic_cast<ImgData*>(data));
    }
    dynamic_cast<CameraState*>(state)->setState(newData);
}

Data* CameraModel::getStateData(std::string data_ID) {
    return state->getState(data_ID);
}
