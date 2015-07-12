/*
 * GateTask.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#include "GateTask.h"
#include "Timer.h"

GateTask::GateTask() {
    // TODO Auto-generated constructor stub
}

GateTask::GateTask(Model* fpgaModel, DepthTask* depthTask, TurnTask* turnTask, SpeedTask* speedTask) {
    this->fpgaModel = fpgaModel;
    this->depthTask = depthTask;
    this->turnTask = turnTask;
    this->speedTask = speedTask;
}

void GateTask::execute() {
    logger->trace("Starting Gate Task");
    Timer timer;
    timer.start();
    depthTask->setDepthAbsolute(POOL_SURFACE_HEIGHT);
    depthTask->execute();
    while (timer.getTimeElapsed() < 5) {
        FPGAData* data = dynamic_cast<FPGAData*>(fpgaModel->getStateData("raw"));
        turnTask->setYawAbsolute(data->getYaw());
        turnTask->execute();
    }
    depthTask->setDepthDelta(100);
    depthTask->execute();
    timer.start();
    while (timer.getTimeElapsed() < 5) {
        //wait for sub to stabilize
    }
    speedTask->setTargetSpeed(30);
    speedTask->execute();
    timer.start();
    while (timer.getTimeElapsed() < 10) {
        //moving...
    }
    speedTask->setTargetSpeed(-30);
    speedTask->execute();
    timer.start();
    while (timer.getTimeElapsed() < 3) {
        //slowing down
    }
    speedTask->setTargetSpeed(0);
    speedTask->execute();
    depthTask->setDepthAbsolute(POOL_SURFACE_HEIGHT);
    depthTask->execute();
    logger->info("Gate Task complete");
}

GateTask::~GateTask() {
    delete logger;
}

