/*
 * TaskFactory.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ed
 */

#ifndef TASKFACTORY_H_
#define TASKFACTORY_H_

#include "Task.h"
#include "PowerTask.h"
#include "MotorTask.h"
#include "TurnTask.h"
#include "DepthTask.h"
#include "SpeedTask.h"
#include "GateTask.h"
#include "PathTask.h"
#include <string>


class TaskFactory {
public:
    /**
     * Contructor
     */
    TaskFactory();

    /**
     * given a string, dynamically create new Tasks
     * @param input the name of the new task
     */
    static Task* newTask(const std::string input);

    static GateTask* createGateTask(Model* fpgaModel, int& targetDepth, int& targetYaw);

    static PathTask* createPathTask(Model* downCamModel, Model* fpgaModel, int& targetYaw);

    static TurnTask* createTurnTask(Model* fpgaModel, int& targetYaw, int delta);

    static DepthTask* createDepthTask(Model* fpgaModel, int& targetDepth, int delta);

    static SpeedTask* createSpeedTask(Model* fpgaModel, int targetSpeed);

    static PowerTask* createPowerTask(Model* fpgaModel);

    static MotorTask* createMotorTask(Model* fpgaModel);

    /**
     * Destructor
     */
    virtual ~TaskFactory();

};

#endif /* SUBZERO_SRC_CONTROLLER_COMMAND_TASKFACTORY_H_ */
