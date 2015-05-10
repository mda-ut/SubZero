/*
 * Command.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef COMMAND_H_
#define COMMAND_H_

class Command {
public:
	/**
	 * Constructor
	 * @param inputTask The task to be done
	 */
	Command(BaseTask *inputTask);

	/**
	 * Destructor
	 */
	virtual ~Command();

	/**
	 * execute the current task
	 */
	virtual void execute() = 0;

private:
	BaseTask *currentTask;

};

#endif /* COMMAND_H_ */
