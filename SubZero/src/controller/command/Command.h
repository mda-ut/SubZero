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
	Command(Task *inputTask){
		//*currentTask=inputTask;
	}
	virtual ~Command();

private:
	Task *currentTask;

	void execute{
		//currentTask.execute();
	}
	//some execute function
};

#endif /* COMMAND_H_ */
