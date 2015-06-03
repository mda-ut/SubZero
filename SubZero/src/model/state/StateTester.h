/*
 * StateTester.h
 *
 *  Created on: May 30, 2015
 *      Author: james
 */

#ifndef SUBZERO_SRC_MODEL_STATE_STATETESTER_H_
#define SUBZERO_SRC_MODEL_STATE_STATETESTER_H_

#include "CameraState.h"
#include "../../util/Logger.h"

class StateTester{
public:
	static void run();
private:
	ImgData* generateImgData(std::string id, std::string msg);
	std::vector<ImgData*> generateImgVector(int i);
	std::string testBasics();
	std::string testSize();
};



#endif /* SUBZERO_SRC_MODEL_STATE_STATETESTER_H_ */
