/*
 * MotorTask.h
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#ifndef MOTOR_TASK_H_
#define MOTOR_TASK_H_

#include "Task.h"
#include "Logger.h"

class MotorTask : public Task {
private:
    Logger* logger = new Logger("MotorTask");
    Model* fpgaModel;

public:
    /**
     * Contructor
     */
    MotorTask();
    MotorTask(Model* fpgaModel);

    void execute();

    /**
     * Destructor
     */
    virtual ~MotorTask();

};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_MOTORTASK_H_ */
