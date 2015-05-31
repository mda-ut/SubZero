/*
 * TouchBuoy.h
 *
 *  Created on: May 9, 2015
 *      Author: ed
 */

#ifndef SUBZERO_SRC_CONTROLLER_TASK_TOUCHBUOY_H_
#define SUBZERO_SRC_CONTROLLER_TASK_TOUCHBUOY_H_

#include "BaseTask.h"



class TouchBuoy: public BaseTask {
public:
	TouchBuoy();
	virtual ~TouchBuoy();

	void execute();
};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_TOUCHBUOY_H_ */
