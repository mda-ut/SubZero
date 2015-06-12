/*
 * TaskFactory.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ed
 */

#ifndef TASKFACTORY_H_
#define TASKFACTORY_H_

#include "Task.h"
#include <string>

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

    static Task* newTask(const std::string input);

	/**
	 * Destructor
	 */
	virtual ~TaskFactory();

};

#endif /* SUBZERO_SRC_CONTROLLER_COMMAND_TASKFACTORY_H_ */
