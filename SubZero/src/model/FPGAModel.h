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
    FPGAModel(State* inputState, HwInterface* inputInterface);

    virtual ~FPGAModel();

/* **************** Data Management **************** */

    /**
     * This sends command to the FPGA to control the sub.
     * @param	cmd		string command sent by Controller
     */
    void sendCommand(std::string cmd);

    /**
     * This gets the newest Data* from the CameraInterface buffer.
     * @return	pointer to the newest data
     */
    Data* getDataFromBuffer();

    /**
     * This package all the filtered FPGA data of the same instance into a vector.
     * @return	vector of pointers to raw and filtered data
     */
    std::vector<Data*> constructDataSet();

    /**
     * This stores the vector of data pointer to FPGAState.
     * @param	dataSet	vector containing data pointers of raw and filtered FPGA data
     */
    void storeToState(std::vector<Data*> dataSet);

    /**
     * This automate the process of getting FPGA data from buffer, pack raw and filtered data together and store into state.
     */
    bool dataTransfer();

};


#endif /* FPGAMODEL_H_ */
