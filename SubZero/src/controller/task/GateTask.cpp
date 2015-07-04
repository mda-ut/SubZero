/*
 * GateTask.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#include "GateTask.h"

GateTask::GateTask() {
    // TODO Auto-generated constructor stub
}

GateTask::GateTask(DepthTask* depthTask, SpeedTask* speedTask) {
    this->depthTask = depthTask;
    this->speedTask = speedTask;
}

void GateTask::execute() {
    //TODO: Wait a few seconds to direct SubZero
    depthTask->execute();
    //TODO: Wait a second to regain stability
    speedTask->execute();
    //TODO: Stop SubZero after a few seconds
    logger->info("Gate Task complete");
}

GateTask::~GateTask() {
    delete logger;
}

