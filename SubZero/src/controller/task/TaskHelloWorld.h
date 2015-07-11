/*
 * TaskA.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ed
 */

#ifndef TASKHELLOWORLD_H_
#define TASKHELLOWORLD_H_

#include "Task.h"

//This is a dummy task class
class TaskHelloWorld : public Task {
public:
	/**
	 * Dummy Contructor
	 */
    TaskHelloWorld();
	/**
	 * Virtual Destructor
	 */
    virtual ~TaskHelloWorld();

	/**
	 * virtual execute function
	 */
    void execute();
};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_TASKHELLOWORLD_H_ */
