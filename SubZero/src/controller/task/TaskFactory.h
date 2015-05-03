/*
 * BaseTaskFactory.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ed
 */

#ifndef BASETASKFACTORY_H_
#define BASETASKFACTORY_H_

#include "BaseTask.h"

class TaskFactory {
public:
	/**
	 * Contructor
	 */
	TaskFactory();

	/**
	 * given a string, dynamically create new Tasts
	 * @param input the name of the new task
	 */

	static BaseTask* newTask(const std::string input);


	/**
	 * Destructor
	 */
	virtual ~TaskFactory();

};

#endif /* SUBZERO_SRC_CONTROLLER_COMMAND_TASKFACTORY_H_ */
