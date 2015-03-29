/*
 * FPGAModel.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef FPGAMODEL_H_
#define FPGAMODEL_H_

#include "Model.h"
#include "FPGAState.h"

/**
 * This is a concrete child of the Model class. It implements functions
 * specific to communicating with the FGPA.
 */
class FPGAModel: public Model {

public:

	/**
	 * This is a constructor of FPGAModel. It will pass the two parameters to parent Model's constructor.
	 * @param	inputState		an observable pointer that is expected to be a FPGAState pointer
	 * @param	inputInterface	a HwInterface pointer that is expected to be a FPGAInterface pointer
	 */
	FPGAModel(Observable* inputState, HwInterface* inputInterface);

	virtual ~FPGAModel();

/* **************** HwInterface related **************** */

	/**
	 * This gets the Data pointer from the buffer and store the Data pointer at the destination.
	 * @param	dataDestination		an empty Data pointer that is filled up after running the function
	 * @return 						error message of the result of this function
	 */
	int getDataFromBuffer(Data* dataDestination);


};


#endif /* FPGAMODEL_H_ */
