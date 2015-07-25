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

CompetitionTask *TaskFactory::createCompetitionTask(Model *forwardCamModel, Model *downCamModel, Model *fpgaModel, int &targetDepth, int &targetYaw) {
    PowerTask* powerTask = TaskFactory::createPowerTask(fpgaModel);
    MotorTask* motorTask = TaskFactory::createMotorTask(fpgaModel);
    GateTask* gateTask = TaskFactory::createGateTask(fpgaModel, targetDepth, targetYaw);
    PathTask* pathTask = TaskFactory::createPathTask(downCamModel, fpgaModel, targetYaw);
    BuoyTask* buoyTask = TaskFactory::createBuoyTask(forwardCamModel, fpgaModel, targetDepth, targetYaw);
    return new CompetitionTask(powerTask, motorTask, gateTask, pathTask, buoyTask);
}

GateTask* TaskFactory::createGateTask(Model *fpgaModel, int& targetDepth, int& targetYaw) {
    DepthTask* depthTask = TaskFactory::createDepthTask(fpgaModel, targetDepth, 100);
    TurnTask* turnTask = TaskFactory::createTurnTask(fpgaModel, targetYaw, 0);
    SpeedTask* speedTask = TaskFactory::createSpeedTask(fpgaModel, 0);
    return new GateTask(fpgaModel, depthTask, turnTask, speedTask);
}

PathTask *TaskFactory::createPathTask(Model *downCamModel, Model *fpgaModel, int &targetYaw) {
    TurnTask* turnTask = TaskFactory::createTurnTask(fpgaModel, targetYaw, 0);
    SpeedTask* speedTask = TaskFactory::createSpeedTask(fpgaModel, 0);
    return new PathTask(downCamModel, turnTask, speedTask);
}

BuoyTask* TaskFactory::createBuoyTask(Model *forwardCamModel, Model *fpgaModel, int& targetDepth, int& targetYaw){
    DepthTask* depthTask = TaskFactory::createDepthTask(fpgaModel, targetDepth, 100);
    TurnTask* turnTask = TaskFactory::createTurnTask(fpgaModel, targetYaw, 0);
    SpeedTask* speedTask = TaskFactory::createSpeedTask(fpgaModel, 0);
    return new BuoyTask(forwardCamModel, turnTask, speedTask, depthTask);
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
