/*
 * SpeedTask.h
 *
 *  Created on: Jul 3, 2015
 *      Author: lrac
 */

#ifndef SPEEDTASK_H_
#define SPEEDTASK_H_

#include "Task.h"
#include "Logger.h"

class SpeedTask : public Task {
private:
    Logger* logger = new Logger("SpeedTask");
    Model* fpgaModel;
    int targetSpeed;

public:
    /**
     * Contructor
     */
    SpeedTask(Model* fpgaModel, int targetSpeed);

    void execute();

    /**
     * Destructor
     */
    virtual ~SpeedTask();

};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_SPEEDTASK_H_ */
