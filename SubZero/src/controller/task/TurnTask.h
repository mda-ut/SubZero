/*
 * TurnTask.h
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#ifndef TURNTASK_H_
#define TURNTASK_H_

#include "Task.h"
#include "Logger.h"

class TurnTask : public Task {
private:
    Logger* logger = new Logger("TurnTask");
    Model* fpgaModel;
    int* currentYawTarget;
    int delta;

public:
	/**
	 * Contructor
	 */
    TurnTask();
    TurnTask(Model* fpgaModel, int& currentYawTarget, int delta);

    void execute();

	/**
	 * Destructor
	 */
    virtual ~TurnTask();

};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_TURNTASK_H_ */
