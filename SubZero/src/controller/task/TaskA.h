/*
 * TaskA.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ed
 */

#ifndef TASKA_H_
#define TASKA_H_

#include "BaseTask.h"

//This is a dummy task class
class TaskA : public BaseTask {
public:
	/**
	 * Dummy Contructor
	 */
	TaskA();
	/**
	 * Virtual Destructor
	 */
	virtual ~TaskA();

	/**
	 * virtual execute function
	 */
    void execute();
};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_TASKA_H_ */
