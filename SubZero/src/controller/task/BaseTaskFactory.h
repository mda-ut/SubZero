/*
 * TaskFactory.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ed
 */

#ifndef TASKFACTORY
#define TASKFACTORY

#include "BaseTask.h"

class TaskFactory {
public:
	TaskFactory();

	//given a string, dynamically create new Tasts
	static BaseTask *newTask(const std::string input);

	virtual ~TaskFactory();

};

#endif /* SUBZERO_SRC_CONTROLLER_COMMAND_TASKFACTORY_H_ */
