/*
 * DepthTask.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: lrac
 */

#include "DepthTask.h"
#include "FPGAInterface.h"


DepthTask::DepthTask(Model* fpgaModel, int& currentTargetDepth, int delta) {
    this->fpgaModel = fpgaModel;
    this->currentTargetDepth = &currentTargetDepth;
    targetDepth = currentDepthTarget + delta;
}

void DepthTask::setDepthDelta(int delta) {
    setDepthAbsolute(*currentDepthTarget + delta);
}

void DepthTask::setDepthAbsolute(int newTargetDepth) {
    targetDepth = newTargetDepth;
}


void DepthTask::execute() {
    if (fpgaModel != 0) {
        logger->info("Moving left");

        fpgaModel->sendCommand(DEPTH, *currentDepthTarget);
        *currentDepthTarget = targetDepth;

        logger->info("Target depth set to " + std::to_string(*currentDepthTarget));
    } else {
        logger->warn("Model is null");
    }
}

DepthTask::~DepthTask() {
    delete logger;
}

