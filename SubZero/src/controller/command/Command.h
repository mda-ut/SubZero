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
	Command(BaseTask *inputTask);
		//*currentTask=inputTask;

	virtual ~Command();
	void execute();

private:
	BaseTask *currentTask;


		//currentTask.execute();

	//some execute function
};

#endif /* COMMAND_H_ */
