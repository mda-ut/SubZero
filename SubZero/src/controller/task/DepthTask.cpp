/*
 * DepthTask.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: lrac
 */

#include "DepthTask.h"
#include "FPGAInterface.h"


DepthTask::DepthTask(Model* fpgaModel, int& currentDepthTarget, int delta) {
    this->fpgaModel = fpgaModel;
    this->currentDepthTarget = &currentDepthTarget;
    this->delta = delta;
}

void DepthTask::execute() {
    if (fpgaModel != 0) {
        logger->info("Moving left");

        *currentDepthTarget += delta;
        fpgaModel->sendCommand(DEPTH, *currentDepthTarget);
        logger->info("Target depth set to " + std::to_string(*currentDepthTarget));
    } else {
        logger->warn("Model is null");
    }
}

DepthTask::~DepthTask() {
    delete logger;
}

