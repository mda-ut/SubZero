/*
 * TaskHeyTonight.h
 *
 *  Created on: Jun 11, 2015
 *      Author: LuckyChewie, gabrielarpino, zSean
 */

#ifndef TASKHEYTONIGHT_H_
#define TASKHEYTONIGHT_H_

#include "BaseTask.h"

//This is a dummy task class
class TaskHeyTonight : public BaseTask {
public:
	/**
	 * Dummy Contructor
	 */
    TaskHeyTonight();
	/**
	 * Virtual Destructor
	 */
    virtual ~TaskHeyTonight();

	/**
	 * virtual execute function
	 */
    void execute();
};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_TASKHEYTONIGHT_H_ */
