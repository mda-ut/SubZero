/*
 * FPGAModel.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "FPGAModel.h"

namespace std {

FPGAModel::FPGAModel() {
	fpgaState = (FPGAState*) &observable;

}

FPGAModel::~FPGAModel() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
