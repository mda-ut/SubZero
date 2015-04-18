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


#endif /* FPGAMODEL_H_ */
