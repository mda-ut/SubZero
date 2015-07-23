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
#include "CameraInterface.h"

/**
 * This is a concrete model child that inherits from Model. It implements functions
 * specific to communicating with the camera. CameraModel will use the protected
 * fields of Model for functions inside CameraModel.
 */
class CameraModel : public Model {

private:
    Logger* logger = new Logger("CameraModel");

public:

    /**
     * This is a constructor of CameraModel. It will pass the two parameters to parent Model's constructor.
     * @param	inputState		an observable pointer that is expected to be a CameraState pointer
     * @param	inputInterface	a HwInterface pointer that is expected to be a CameraInterface pointer
     */
    CameraModel(State* inputState, HwInterface* inputInterface, double frequency);

    virtual ~CameraModel();


/* **************** Data Management **************** */

    /**
     * This sends command to the FPGA to control the camera.
     * @param	cmd		string command sent by Controller
     */
    virtual void sendCommand(Attributes attr, int value);

    /**
     * This package all the filtered Camera data of the same instance into a vector.
     * @return	vector of pointers to raw and filtered data
     */
    virtual std::vector<Data*> constructDataSet(Data* rawData);

    /**
     * This stores the vector of data pointer to CameraState.
     * @param	dataSet	vector containing data pointers of raw and filtered images
     */
    virtual void storeToState(std::vector<Data*> dataSet);

    /**
     * Return the model's current state
     * @return
     */
    virtual Data* getStateData(std::string data_ID);
};


#endif /* CAMERAMODEL_H_ */
