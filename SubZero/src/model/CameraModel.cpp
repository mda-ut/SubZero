/*
 * CameraModel.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "CameraModel.h"

namespace std {

CameraModel::CameraModel(Observable* state, HwInterface* interface):Model(state,interface) {
	cameraState = (CameraState*)Model::getObservable();
	cameraInterface = (CameraInterface*)Model::getHwInterface();

}

CameraModel::~CameraModel() {
	// TODO Auto-generated destructor stub
}

RGBFilter* Model::createRGBFilter(std::string filterIDandRGB){
	int R, G, B;
	std::string ID;
	return FilterFactory::createRGBFilter(std::string ID, int R, int G, int B);
}


} /* namespace std */
