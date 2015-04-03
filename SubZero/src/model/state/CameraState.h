/*
 * CameraState.h
 *
 *  Created on: Feb 7, 2015
 *      Author: carl, james
 */

#ifndef CAMERASTATE_H_
#define CAMERASTATE_H_
#include "Observable.h"
#include "State.h"
#include "ImgData.h"	//rename it to whatever its called

#include <list>
#include <vector>


/**
 * CameraState is an Observable used by CameraModel to hold data sent from cameras.
 */

class CameraState : public State, public Observable {

	//all of this class' variables are inherited from its parent (State.h)

public:
	/**
	 * constructor
	 */
	CameraState();

	/**
	 * destructor
	 */
	virtual ~CameraState();

	/**
	 * Sets the state
	 * SHOULD ONLY BE CALLED AFTER startFrame() IS CALLED
	 * OR ELSE IT WOULD THROW FrameNotStartedException
	 * @param image data to be set for this frame
	 * @throws FrameNotStartedException
	 */
	void setState(ImgData data);


	void setStates(std::vector<ImgData> v);

	/**
	 * Returns a reference to a deep copy of an image specified with the _id_ at _t_ frames before this call
	 * @param id = id of the image that is needed
	 			t = how many frames ago was the image stored
	 */
	ImgData getState (std::String id, int t);

	/**
	 * Returns a reference to a deep copy of the latest image specified with the _id_
	 * (same as calling getImage(id, 0))
	 * @param id = id of the image that is needed
	 */
	ImgData getState (std::String id);

	/**
	 * Gets the newest raw image
	 */
	ImgData getRaw();

	/**
	 * Gets the raw image _t_ frames before
	 */
	ImgData getRaw(int t);

};

#endif /* SRC_MODEL_STATE_CAMERASTATE_H_ */
