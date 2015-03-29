/*
 * BaseTaskFactory.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ed
 */

#ifndef BASETASKFACTORY_H_
#define BASETASKFACTORY_H_

#include "BaseTask.h"

class BaseTaskFactory {
public:
	BaseTaskFactory();

	//given a string, dynamically create new Tasts
	static BaseTask* newTask(const std::string input);

	virtual ~BaseTaskFactory();

};

#endif /* SUBZERO_SRC_CONTROLLER_COMMAND_TASKFACTORY_H_ */
