/*
 * FPGAInterface.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef SUBZERO_SRC_MODEL_INTERFACE_FPGAINTERFACE_H_
#define SUBZERO_SRC_MODEL_INTERFACE_FPGAINTERFACE_H_

#include "HwInterface.h"

namespace std {

class FPGAInterface: public HwInterface {
public:
	FPGAInterface();
	virtual ~FPGAInterface();
};

} /* namespace std */

#endif /* SUBZERO_SRC_MODEL_INTERFACE_FPGAINTERFACE_H_ */
