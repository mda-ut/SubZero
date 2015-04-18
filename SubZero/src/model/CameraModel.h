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
	 * This is a constructor of CameraModel. It will pass the two parameters to parent Model's constructor.
	 * @param	inputState		an observable pointer that is expected to be a CameraState pointer
	 * @param	inputInterface	a HwInterface pointer that is expected to be a CameraInterface pointer
	 */
	CameraModel(Observable* inputState, HwInterface* inputInterface);

	virtual ~CameraModel();

	/**
	 * This return the most recent Data* from the buffer.
	 * @return 	pointer to the most recent data
	 */
	Data* getDataFromBuffer();

	/**
	 * store2State stores a vector of Data* to state. The vector contains Data at the same time.
	 * @param	dataSet		the Data pointer that needs to be stored
	 * @return				error message of the result of this function
	 */
	int storeToState(std::vector<Data*> dataSet);

};


#endif /* CAMERAMODEL_H_ */
