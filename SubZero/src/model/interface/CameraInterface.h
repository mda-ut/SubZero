/*
 * CameraInterface.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef CAMERAINTERFACE_H_
#define CAMERAINTERFACE_H_

#include "HwInterface.h"
// include other camera + image specific classes
// #include blahhhhhh~

/**
 * A child of HwInterface that deals specifically with the camera. Concrete class.
 */

class CameraInterface: public HwInterface {
public:
	CameraInterface();
	/**
	 * Constructor
	 */
	virtual ~CameraInterface();
	/**
	 * Deconstructor
	 */
};


#endif 


/* CAMERAINTERFACE_H_ */