/*
 * CameraModel.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef CAMERAMODEL_H_
#define CAMERAMODEL_H_

#include "Model.h"
#include "CameraState.h"

/**
 * This is a concrete model child that inherits from Model. It implements functions
 * specific to communicating with the camera. CameraModel will use the protected
 * fields of Model for functions inside CameraModel.
 */
class CameraModel: public Model {

public:

	/**
	 * CameraModel construct takes in two parameters and call Model constructor to assign Model protected fields.
	 * @param inputState is an Observable pointer and inputInterface is a HwInterface pointer.
	 */
	CameraModel(Observable* inputState, HwInterface* inputInterface);

	virtual ~CameraModel();

/* **************** HwInterface related **************** */

	int getDataFromBuffer(Data* dataDestination);

};


#endif /* CAMERAMODEL_H_ */
