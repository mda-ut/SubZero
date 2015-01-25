/*
 * CameraModel.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef CAMERAMODEL_H_
#define CAMERAMODEL_H_

#include "Model.h"

namespace std {
/**
 * This is a concrete child of the Model class. It implements functions
 * specific to communicating with the camera.
 */

class CameraModel: public Model {
public:
	CameraModel();
	/**
	 * Constructor
	 */
	virtual ~CameraModel();
	/**
	 * Deconstructor
	 */
};

} /* namespace std */

#endif /* CAMERAMODEL_H_ */
