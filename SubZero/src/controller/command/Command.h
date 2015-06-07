/*
 * Command.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include "../task/BaseTask.h"

class Command {
public:
	/**
	 * execute the current task
	 */
    virtual void execute() = 0;

private:
	BaseTask *currentTask;

};

#endif /* COMMAND_H_ */
