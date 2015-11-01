/*
 * FPGAModel.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef FPGAMODEL_H_
#define FPGAMODEL_H_

#include "Model.h"
#include "state/FPGAState.h"
#include "interface/HwInterface.h"
#include "interface/FPGAInterface.h"

/**
 * This is a concrete child of the Model class. It implements functions
 * specific to communicating with the FGPA.
 */
class FPGAModel: public Model {

private:
    Logger* logger = new Logger("FPGAModel");

public:

    /**
     * This is a constructor of FPGAModel. It will pass the two parameters to parent Model's constructor.
     * @param	inputState		an observable pointer that is expected to be a FPGAState pointer
     * @param	inputInterface	a HwInterface pointer that is expected to be a FPGAInterface pointer
     */
    FPGAModel(State* inputState, HwInterface* inputInterface, double frequency);

    virtual ~FPGAModel();

/* **************** Data Management **************** */

    /**
     * This sends command to the FPGA to control the sub.
     * @param	cmd		string command sent by Controller
     */
    virtual void sendCommand(Attributes attr, int value);

    /**
     * This package all the filtered FPGA data of the same instance into a vector.
     * @return	vector of pointers to raw and filtered data
     */
    virtual std::vector<Data*> constructDataSet(Data* rawData);

    /**
     * This stores the vector of data pointer to FPGAState.
     * @param	dataSet	vector containing data pointers of raw and filtered FPGA data
     */
    virtual void storeToState(std::vector<Data*> dataSet);

    /**
     * Return the model's current state
     * @return
     */
    virtual Data* getStateData(std::string data_ID);
};


#endif /* FPGAMODEL_H_ */
