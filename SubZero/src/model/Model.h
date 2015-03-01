/*
 * Model.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef MODEL_H_
#define MODEL_H_

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
	FilterFactory* filterFactory;

public:
	/**
	 * This is the main constructor of a Model object.
	 * @param	fM	This is the only parameter, a reference to FilterManager, to this Model constructor.
	 */
	Model(FilterManager* fM);

	/**
	 * This is the overload of the constructor of a Model object with one additional FilterFactory parameter.
	 * @param	fM	This is the first parameter to the overload constructor.
	 * @param	fF	This is the second parameter to the overload constructor if a FilterFactory object is created.
	 */
	Model(FilterManager* fM, FilterFactory* fF);

	/**
	 * This is the destructor of Model.
	 * @return	Nothing.
	 */
	virtual ~Model();
};

#endif /* MODEL_H_ */
