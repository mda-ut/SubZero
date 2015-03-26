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
public:

	/**
	 * Model constructor
	 */
	Model(Observable* inputObservable, HwInterface* inputHwInterface);

	/**
	 * Model destructor
	 */
	virtual ~Model();

/* **************** HwInterface related **************** */

	/**
	 * getDataFromBuffer gets a Data pointer from HwInterface buffer. CreateData is called inside getDataFromBuffer.
//	 * @param DataDestination is an empty Data pointer that is filled up after running the function
//   * @return int determines if the function is run successfully
	 */
	virtual int getDataFromBuffer(Data* dataDestination)=0;

//	/**
//	 * getImageFromBuffer gets an ImageData* from image buffer of HwInterface
//	 * @param imageDestination is an empty ImageData pointer that is filled up after running the function
//   * @return int determines if the function is run successfully
//   */
//	int getImageFromBuffer(ImageData* imageDestination);
//
//	/**
//	 * getFPGAFromBuffer gets an FPGAData* from FPGA buffer of HwInterface
//	 * @param fpgaDestination is an empty FPGAData pointer that is filled up after running the function
//	 * @return int determines if the function is run successfully
//	 */
//	int getFPGAFromBuffer(FPGAData* fpgaDestination);

	/**
	 * sendCommand send a command to the FPGA
	 * @param command2Send contains the command and will be parsed before sending
	 * @return int determines if the function is run successfully
	 */
	int sendCommand(std::string command2Send);

/* **************** Observable/State related **************** */

	/**
	 * notifyObserver notifies all observers of the observable that an update arrives
	 * @return int determines if the function is run successfully
	 */
	int notifyObserver();

	/**
	 * store2State stores one Data pointer to state vector
	 * @param data2Store is the Data pointer to store
	 * @return int determines if the function is run successfully
	 */
	int store2State(Data* data2Store);

/* **************** FilterManager related **************** */

	int insertFilter(std::string filterID, int insertIndex);

	int replaceFilter(std::string filterID, int replaceIndex);

	int deleteFilter(std::string filterID);

	int deleteFilter(int deleteIndex);

	int getFilterChainSize();

	std::string getFMFilterID();

	std::string getFMTaskID();

	int getIndexByID(std::string filterID);

	std::string getIDByIndex(int filterIndex);

	int createFM(std::string taskID);

	int store2FMVector(FM* filterManager2Store);

	int deleteFM(std::string taskID);

	FilterManager* getFM(std::string taskID);

/* **************** FilterFactory related **************** */

	int CreateFilters();


/*
	static RGBFilter * createRGBFilter(std::string filterIDandRGB);

	void applyFilterChain();

	void insertFilter(Filter * filter);

	void insertFilter(Filter * filter, int index);

	void replaceFilter(Filter * filter, int index);

	void deleteFilterByID(std::string ID);

	void deleteFilterByID(std::string ID, int type);

	void deleteFilterByIndex(int index);

	void deleteFilterByIndex(std::vector<int> indices);

	int getSizeOfFilter();

	std::vector getFilterChainID();

	int getFilterIndexByID(std::string ID);

	std::vector getFilterIndexByID(std::string ID, int type);
*/

};

#endif /* MODEL_H_ */
