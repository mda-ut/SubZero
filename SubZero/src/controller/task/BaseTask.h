/*
 * BaseTask.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef TASK_H_
#define TASK_H_

#include "TaskA.h"

class BaseTask {
public:

	//The BaseTask class is purely virtual
	BaseTask();
	virtual ~BaseTask();

	virtual void execute()= 0;

 private:

};

#endif /* TASK_H_ */
