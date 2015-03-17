/*
 * Model.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "FilterManager.h"
#include "FilterFactory.h"
#include "Observable.h"

#include <string>

using namespace std;

/**
 * This is an abstract class that represents the physical attributes of the sub.
 * It accepts input from cameras and FPGA and outputs to FPGA and
 * cameras (strictly speaking). Model contains references to the tools required
 * for the assets to run. Each Model inherits from observable and has a state.
 * Each Model has a filter.
 *
 * @author	Zack Tzeng
 * @version	0.0
 * @since	2014-03-01
 */
class Model {

private:
	FilterManager* filterManager;

protected:
	Observable* observable;

public:
	/**
	 * This is the main constructor of a Model object.
	 * @param	fM	This is the only parameter, a reference to FilterManager, to this Model constructor.
	 */
	Model(FilterManager* inputFM, State* inputState);

	/**
	 * This is the destructor of Model.
	 * @return	Nothing.
	 */
	virtual ~Model();
};

#endif /* MODEL_H_ */
