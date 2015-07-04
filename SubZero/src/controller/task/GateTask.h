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
#include "SpeedTask.h"
#include "Logger.h"

class GateTask : public Task {
private:
    Logger* logger = new Logger("GateTask");
    DepthTask* depthTask;
    SpeedTask* speedTask;

public:
    /**
     * Contructor
     */
    GateTask();
    GateTask(DepthTask* depthTask, SpeedTask* speedTask);

    void execute();

    /**
     * Destructor
     */
    virtual ~GateTask();

};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_GATETASK_H_ */
