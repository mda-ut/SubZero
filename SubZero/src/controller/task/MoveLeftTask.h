/*
 * MoveLeftTask.h
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#ifndef MOVELEFTTASK_H_
#define MOVELEFTTASK_H_

#include "Task.h"
#include "Logger.h"

class MoveLeftTask : public Task {
private:
	Logger* logger = new Logger("MoveLeftTask");

public:
	/**
	 * Contructor
	 */
	MoveLeftTask();
	MoveLeftTask(std::vector<Model*> models);

    void execute();

	/**
	 * Destructor
	 */
	virtual ~MoveLeftTask();

};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_MOVELEFTTASK_H_ */
