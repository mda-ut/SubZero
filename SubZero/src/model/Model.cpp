/*
 * Model.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Model.h"

Model::Model(Observable* inputObservable, HwInterface* inputHwInterface)
{
	this->state = inputObservable;
	this->interface = inputHwInterface;
	this->modelType = CAMERAMODEL; // Initialize modelType to CAMERAMODEL;
}

Model::~Model()
{
	// TODO Auto-generated destructor stub
}
