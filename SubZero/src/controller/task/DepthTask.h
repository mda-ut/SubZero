/*
 * DepthTask.h
 *
 *  Created on: Jul 3, 2015
 *      Author: lrac
 */

#ifndef DEPTHTASK_H_
#define DEPTHTASK_H_

#include "Task.h"
#include "Logger.h"

class DepthTask : public Task {
private:
    Logger* logger = new Logger("DepthTask");
    Model* fpgaModel;
    int* currentTargetDepth;
    int targetDepth;

public:
    /**
     * Contructor
     */
    DepthTask(Model* fpgaModel, int& currentTargetDepth, int delta = 50);

    void execute();

    /**
     * Destructor
     */
    virtual ~DepthTask();

    void setDepthDelta(int Delta);
    void setDepthAbsolute(int newDepth);
};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_DEPTHTASK_H_ */
