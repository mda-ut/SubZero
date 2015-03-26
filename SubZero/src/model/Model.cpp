/*
 * Model.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Model.h"

Model::Model(Observable* inputObservable, HwInterface* inputHwInterface)
{
	this->observable = inputObservable;
	this->hwInterface = inputHwInterface;
}

Model::~Model()
{
	// TODO Auto-generated destructor stub
}

Observable* Model::getObservable(){
	return this->observable;
}

HwInterface* Model::getHwInterface(){
	return this->hwInterface;
}
