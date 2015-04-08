/*
 * Model.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <string>

#include "HwInterface.h"
#include "FilterManager.h"
#include "FilterFactory.h"

enum ModelType{
	CAMERAMODEL = 1,
	FPGAMODEL = 2
};

/**
 * This can have the potential to be an pure virtual (abstract) class, but it's not for now. Modle
 * represents the physical attributes of the sub. It accepts input from cameras and FPGA
 * and outputs to FPGA and cameras (strictly speaking). Model contains references to the tools required
 * for the assets to run. Each Model inherits from observable and has a state.
 * Each Model has a FilterManager.
 *
 * @author	Zack Tzeng
 * @version	0.0
 * @since	2014-03-01
 */
class Model {

protected:
	Observable* state;
	HwInterface* interface;
	std::vector<FilterManager*> filterManagerList;
	ModelType modelType;
public:

	/**
	 * This is the constructor to a parent Model object.
	 * @param	inputObservable		an observable pointer used to create a Model
	 * @param	inputHwInterface	an interface pointer used to create a Model
	 */
	Model(Observable* inputObservable, HwInterface* inputHwInterface);

	/**
	 * Model destructor
	 */
	virtual ~Model();


/* **************** HwInterface related **************** */

	/**
	 * getDataFromBuffer gets a Data pointer from HwInterface buffer. CreateData is called inside getDataFromBuffer.
     * @return	shallow copy of the first Data* in HwInterface buffer
	 */
	virtual Data* getDataFromBuffer();

	/**
	 * sendCommand send a command to the FPGA
	 * @param	newCommand	contains the command and will be parsed before sending
	 * @return				error message of the result of this function
	 */
	virtual int sendCommand(std::string newCommand);


/* **************** Observable/State related **************** */

	/**
	 * notifyObserver notifies all observers of the observable when an update arrives
	 */
	void notifyObserver();

	/**
	 * store2State stores one Data pointer to state vector
	 * @param	dataSet		the Data pointer that needs to be stored
	 * @return				error message of the result of this function
	 */
	int storeToState(std::vector<Data*> dataSet);


/* **************** FilterManager related **************** */

	/**
	 * This inserts a filter to the end of the filter chain.
	 * @param	fmID			the ID of the filter manager to which the new filter is inserted
	 * @param	newFIlter		a pointer to the new filter
	 * @param	newFilterID		the ID of the new filter
	 * @return					error message of the result of this function
	 */
	int insertFilter(std::string fmID, Filter* newFilter, std::string newFilterID);

	/**
	 * This inserts a filter to the target location.
	 * @param	fmID			the ID of the filter manager to which the new filter is inserted
	 * @param	newFIlter		a pointer to the new filter
	 * @param	newFilterID		the ID of the new filter
	 * @param	targetID		the target location of the new filter
	 * 								- It can be a filter ID then new filter is inserted before it.
	 * 								- It can be BEGIN or END then new filter is inserted at the beginning or the end of the chain.
	 * @return					error message of the result of this function
	 */
	int insertFilter(std::string fmID, Filter* newFilter, std::string newFilterID, std::string targetID);

	/**
	 * This replace an existing filter by a new filter.
	 * @param	fmID			the ID of the filter manager to which the new filter is inserted
	 * @param	newFIlter		a pointer to the new filter
	 * @param	newFilterID		the ID of the new filter
	 * @param	targetID		the existing filter to be replaced
	 * @return					error message of the result of this function
	 */
	int replaceFilter(std::string fmID, Filter* newFilter, std::string newFilterID, std::string targetID);

	/**
	 * This delete one or all of the filter in the filter chain.
	 * @param	targetID	the ID of the one filter to be deleted or ALL if all filters should be deleted
	 * @return 				error message of the result of this function
	 */
	int deleteFilter(std::string targetID);

	/**
	 * This return the length of the filter chain.
	 * @param	fmID	the ID of the filter manager to look for the length of the filter chain
	 * @return			the length of the filter chain
	 */
	int getFilterChainSize(std::string fmID);

	/**
	 * This returns the vector of all the filter IDs in the chain.
	 * @param	fmID	the ID of the filter manager
	 * @return			the vector of all the string filter IDs
	 */
	std::vector<std::string> getFilterChainIDs(std::string fmID);

	/**
	 * This returns the vector of all the filter managers in the list.
	 * @return	the vector of all the string filter manager IDs
	 */
	std::vector<std::string> getFMListIDs();

	/**
	 * This creates a filter manager and store it in the provided destination.
	 * @param	fmID			the ID of the filter manager
	 * @param	fmDestination	the filter manager pointer that store the "newed" filter manager
	 * @return					error message of the result of this function
	 */
	int createFM(std::string fmID, FilterManager* fmDestination);

	/**
	 * This stores a newly created filter manager to the filter manager list.
	 * @param	newFM	the pointer to the filter manager that will be stored
	 * @return			error message of the result of this function
	 */
	int storeToFMList(FilterManager* newFM);

	/**
	 * This deletes one or all the filter managers in the list.
	 * @param	fmID	the ID of the filter manager to be deleted or ALL to delete all the filter managers
	 * @return			error message of the result of this function
	 */
	int deleteFM(std::string fmID);

	/**
	 * This return the pointer to a filter manager in the list by its ID.
	 * @param	fmID	the ID of the filter manager that is desired to get
	 * @return			the pointer to the desired filter manager
	 */
	FilterManager* getFM(std::string fmID);

};

#endif /* MODEL_H_ */
