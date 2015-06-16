/*
 * CameraModel.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "CameraModel.h"

void CameraModel::sendCommand(std::string cmd){
// Emma go!!
}

Data* CameraModel::getDataFromBuffer(){
	Data* rawImageData = ((CameraInterface*) &(this->interface))->getDataFromBuffer();
	return rawImageData;
}

std::vector<Data*> CameraModel::constructDataSet(){
	std::vector<Data*> imageDataSet;
	Data* rawImageData = this->getDataFromBuffer();
	imageDataSet.push_back(rawImageData);
	for(std::vector<FilterManager*>::iterator it = this->filterManagerList.begin();it!=filterManagerList.end();++it){
		Data* deepCopyImage = rawImageData; // Check if the operator overload for = is right. Don't know don't know yet
		(*it)->applyFilterChain(deepCopyImage);
		imageDataSet.push_back(deepCopyImage);
	}
	return imageDataSet;
}

void CameraModel::storeToState(std::vector<Data*> dataSet){
	std::vector<ImgData*> newData;
	for(std::vector<Data*>::iterator it = dataSet.begin();it!=dataSet.end();++it){
		newData.push_back((ImgData*)(*it));
	}
	((CameraState*) &(this->state))->setState(newData);
}

void CameraModel::dataTransfer(){
	this->storeToState(constructDataSet());
}
