/*
 * CameraModel.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "CameraModel.h"

CameraModel::CameraModel(Observable* inputState, HwInterface* inputInterface):Model(inputState,inputInterface){}

CameraModel::~CameraModel() {
	// TODO Auto-generated destructor stub
}
