/*
 * StateTester.h
 *
 *  Created on: May 30, 2015
 *      Author: james
 */

#ifndef SUBZERO_SRC_MODEL_STATE_STATETESTER_H_
#define SUBZERO_SRC_MODEL_STATE_STATETESTER_H_

#include "CameraState.h"
#include "FPGAState.h"
#include "../../util/Logger.h"
#include <exception>
#include <iostream>

class StateTester{
public:
	static void run();
private:
	ImgData* generateImgData(std::string id, std::string msg);
	std::vector<ImgData*> generateImgVector(int i);
	bool testImgBasics();
	bool testImgSize();


	FPGAData* generateFPGAData(std::string id, std::string msg);
	std::vector<FPGAData*> generateFPGAVector(int i);
	bool testFPGABasics();
	bool testFPGASize();
};



#endif /* SUBZERO_SRC_MODEL_STATE_STATETESTER_H_ */
