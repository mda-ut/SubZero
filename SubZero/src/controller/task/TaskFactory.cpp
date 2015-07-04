/*
 * TaskFactory.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: ed
 */

#include "TaskFactory.h"
#include "SpeedTask.h"
#include "GateTask.h"

TaskFactory::TaskFactory() {
    // TODO Auto-generated constructor stub

}

GateTask* TaskFactory::createGateTask(Model *fpgaModel, int& targetDepth, int targetSpeed) {
    DepthTask* depthTask = TaskFactory::createDepthTask(fpgaModel, targetDepth, 100);
    SpeedTask* speedTask = TaskFactory::createSpeedTask(fpgaModel, targetSpeed);
    return new GateTask(depthTask, speedTask);
}

TurnTask* TaskFactory::createTurnTask(Model* fpgaModel, int& targetYaw, int delta) {
    return new TurnTask(fpgaModel, targetYaw, delta);
}

DepthTask* TaskFactory::createDepthTask(Model* fpgaModel, int& targetDepth, int delta) {
    return new DepthTask(fpgaModel, targetDepth, delta);
}

SpeedTask* TaskFactory::createSpeedTask(Model* fpgaModel, int targetSpeed) {
    return new SpeedTask(fpgaModel, targetSpeed);
}

PowerTask* TaskFactory::createPowerTask(Model* fpgaModel) {
    return new PowerTask(fpgaModel);
}

MotorTask* TaskFactory::createMotorTask(Model* fpgaModel) {
    return new MotorTask(fpgaModel);
}

TaskFactory::~TaskFactory() {
    // TODO Auto-generated destructor stub
}
