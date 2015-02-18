/*
 * CameraState.h
 *
 *  Created on: Feb 7, 2015
 *      Author: carl
 */

#ifndef CAMERASTATE_H_
#define CAMERASTATE_H_
#include "Observable.h"

/**
 * CameraState is an Observable used by CameraModel to hold data sent from cameras.
 * It can notify any Observers when changes are made.
 */

class CameraState : public Observable {
private:
	double myState;

public:
	/**
	 * constructor
	 */
	CameraState();

	/**
	 * destructor
	 */
	virtual ~CameraState();

	double getState();
	void setState(myState);

};

#endif /* SRC_MODEL_STATE_CAMERASTATE_H_ */
