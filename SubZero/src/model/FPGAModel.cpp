/*
 * FPGAModel.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "FPGAModel.h"

void FPGAModel::sendCommand(std::string cmd){
// Emma go!!
}

Data* FPGAModel::getDataFromBuffer(){
	Data* rawFPGAData = ((FPGAInterface*)&(this->interface))->getDataFromBuffer();
	return rawFPGAData;
}

std::vector<Data*> FPGAModel::constructDataSet(){
	std::vector<Data*> fpgaDataSet;
	Data* rawFPGAData = this->getDataFromBuffer();
	fpgaDataSet.push_back(rawFPGAData);
	for(std::vector<FilterManager*>::iterator it = this->filterManagerList.begin();it!=filterManagerList.end();++it){
		Data* deepCopyFPGA = rawFPGAData; // Check if the operator overload for = is right. Don't know don't know yet
		(*it)->applyFilterChain(deepCopyFPGA);
		fpgaDataSet.push_back(deepCopyFPGA);
	}
	return fpgaDataSet;
}

void FPGAModel::storeToState(std::vector<Data*> dataSet){
	std::vector<FPGAData*> newData;
	for(std::vector<Data*>::iterator it = dataSet.begin();it!=dataSet.end();++it){
		newData.push_back((FPGAData*)(*it));
	}
	((FPGAState*) &(this->state))->setState(newData);
}

void FPGAModel::dataTransfer(){
	this->storeToState(constructDataSet());
}
