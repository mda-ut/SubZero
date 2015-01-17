/*
 * CameraInterface.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef SUBZERO_SRC_MODEL_INTERFACE_CAMERAINTERFACE_H_
#define SUBZERO_SRC_MODEL_INTERFACE_CAMERAINTERFACE_H_

#include "HwInterface.h"

namespace std {

class CameraInterface: public HwInterface {
public:
	CameraInterface();
	virtual ~CameraInterface();
};

} /* namespace std */

#endif /* SUBZERO_SRC_MODEL_INTERFACE_CAMERAINTERFACE_H_ */
