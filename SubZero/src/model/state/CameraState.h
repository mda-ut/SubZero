/*
 * CameraState.h
 *
 *  Created on: Feb 7, 2015
 *      Author: carl, james
 */

#ifndef CAMERASTATE_H_
#define CAMERASTATE_H_
#include "Observable.h"
#include "ImgData.h"	//rename it to whatever its called

#include <list>
#include <vector>

/**
 * CameraState is an Observable used by CameraModel to hold data sent from cameras.
 */

class CameraState : public Observable {
private:

	//boolean to signal if a new frame has started
	bool frameStarted;

	//the max length of the linked list
	//the amount of frames the state will hold
	int maxLength;

	// LinkedList <Vector<ImgData>>
	// Linked list to hold the states for every frame
	// Vector to hold the different states for each frame, filtered and non-filtered
	// not sure if this is how you initalize a linked list of vectors
	std::list<std::vector<ImgData>> stateData;

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
	 * Starts a new Frame
	 * Have to be called before you can call setState()
	 * Only Model should be calling this function (might implement a check for that)
	 */
	void startFrame();

	/**
	 * Ends the frame
	 * Have to be called after startFrame() is called
	 * If called before startFrame, then it does nothing
	 * Be careful when calling this, since you cannot change the frame after it has ended
	 */
	void endFrame();

	/**
	 * Sets the state
	 * SHOULD ONLY BE CALLED AFTER startFrame() IS CALLED
	 * OR ELSE IT WOULD THROW FrameNotStartedException
	 * @param image data to be set for this frame
	 * @throws FrameNotStartedException
	 */
	void setState(ImgData data);

	/**
	 * Returns a deep copy of an image specified with the _id_ at _t_ frames before this call
	 * @param id = id of the image that is needed
	 			t = how many frames ago was the image stored
	 */
	ImgData getState (std::string id, int t);

	/**
	 * Returns a deep copy of the latest image specified with the _id_ 
	 * (same as calling getImage(id, 0))
	 * @param id = id of the image that is needed
	 */
	ImgData getState (std::string id);

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
