/*
 * CameraModel.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef CAMERAMODEL_H_
#define CAMERAMODEL_H_

#include "Model.h"
#include "state/CameraState.h"

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


/* **************** Data Management **************** */

	/**
	 * This sends command to the FPGA to control the camera.
	 * @param	cmd		string command sent by Controller
	 */
	void sendCommand(std::string cmd);

	/**
	 * This gets the newest Data* from the CameraInterface buffer.
	 * @return	pointer to the newest data
	 */
	Data* getDataFromBuffer();

	/**
	 * This package all the filtered Camera data of the same instance into a vector.
	 * @return	vector of pointers to raw and filtered data
	 */
	std::vector<Data*> constructDataSet();

	/**
	 * This stores the vector of data pointer to CameraState.
	 * @param	dataSet	vector containing data pointers of raw and filtered images
	 */
	void storeToState(std::vector<Data*> dataSet);

	/**
	 * This automate the process of getting images from buffer, pack raw and filtered data together and store into state.
	 */
	void dataTransfer();
};


#endif /* CAMERAMODEL_H_ */
