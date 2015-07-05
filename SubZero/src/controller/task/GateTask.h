/*
 * GateTask.h
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#ifndef GATETASK_H_
#define GATETASK_H_

#include "Task.h"
#include "DepthTask.h"
#include "TurnTask.h"
#include "SpeedTask.h"
#include "Logger.h"

class GateTask : public Task {
private:
    Logger* logger = new Logger("GateTask");
    Model* fpgaModel;
    DepthTask* depthTask;
    TurnTask* turnTask;
    SpeedTask* speedTask;

public:
    /**
     * Contructor
     */
    GateTask();
    GateTask(Model* fpgaModel, DepthTask* depthTask, TurnTask* turnTask, SpeedTask* speedTask);

    void execute();

    /**
     * Destructor
     */
    virtual ~GateTask();

};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_GATETASK_H_ */
