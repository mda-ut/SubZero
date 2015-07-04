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

GateTask::GateTask(DepthTask* depthTask, SpeedTask* speedTask) {
    this->depthTask = depthTask;
    this->speedTask = speedTask;
}

void GateTask::execute() {
    Timer timer;
    timer.start();
    depthTask->setDepthAbsolute(POOL_SURFACE_HEIGHT);
    depthTask->execute();
    while (timer.getTimeElapsed() < 5) {
        //wait for diver to align sub
    }
    depthTask->setDepthDelta(100);
    depthTask->execute();
    timer.start();
    while (timer.getTimeElapsed() < 5) {
        //wait for sub to stabilize
    }
    speedTask->setTargetSpeed(30);
    speedTask->execute();
    while (timer.getTimeElapsed() < 12) {
        //moving...
    }
    logger->info("Gate Task complete");
}

GateTask::~GateTask() {
    delete logger;
}

