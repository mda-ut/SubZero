/*
 * CameraState.h
 *
 *  Created on: Feb 7, 2015
 *      Author: carl, james
 */

#ifndef CAMERASTATE_H_
#define CAMERASTATE_H_
#include "../../Observable.h"
#include "State.h"
#include "../../util/data/ImgData.h"


/**
 * CameraState is an Observable used by CameraModel to hold data sent from cameras.
 */

class CameraState : public State {

	//all of this class' variables are inherited from its parent (State.h)
protected:
	std::list<std::vector<ImgData*> > stateData;

public:
	/**
	 * constructor
	 */
	CameraState();
	CameraState(int framesStored);

	/**
	 * destructor
	 */
	virtual ~CameraState();

	/**
	 * Returns a deep copy of the image state specified with the _ID_ at _i_ frames before this call
	 * @param ID = id of the image that is needed
	 * @param i = how many frames ago was the image stored (zero indexed; newest frame = 0)
	 * @return returns the pointer to the deep copied image data
	 */
	ImgData* getState (std::string ID, int i);

	/**
	 * Returns a deep copy of the latest image specified with the _ID_
	 * (same as calling getState(ID, 0))
	 * @param ID = id of the image that is needed
	 * @return returns the pointer to a deep copied image data
	 */
	ImgData* getState (std::string ID);

	/**
	 * Sets the state
	 * SHOULD ONLY BE CALLED AFTER startFrame() IS CALLED
	 * @param d = Pointer to image data to be set for this frame
	 * @return an int indicating whether a operation was successful
	 */
	//int setState(ImgData* d);

	/**
	 * Same thing as setState, except it takes an entire vector of data instead of 1 data
	 * Sets the state
	 * SHOULD ONLY BE CALLED AFTER startFrame() IS CALLED
	 * @param d = vector of image data to be set for this frame
	 * @return an int indicating whether the operation was successful
	 *  	- 0 = successful
	 *  	- 1 = called this function before startFrame is called
	 */
	int setState(std::vector<ImgData*> d);

	/**
	 * Gets a pointer to a deep copy of the newest raw image data
	 * @return a pointer to the deep copy of the raw image data
	 */
	ImgData* getRaw();

	/**
	 * Gets a pointer to the deep copy of the raw image data _i_ frames before
	 * @param i = how many frames ago the raw image was recorded (zero indexed; newest frame = 0)
	 * @return a pointer to the deep copy of the raw State data _i_ frames before this function call
	 */
	ImgData* getRaw(int i);

};

#endif /* SRC_MODEL_STATE_CAMERASTATE_H_ */
