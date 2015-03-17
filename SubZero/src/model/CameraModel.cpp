/*
 * CameraModel.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "CameraModel.h"

namespace std {

CameraModel::CameraModel() {
	cameraState = (CameraState*) &observable;

}

CameraModel::~CameraModel() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
