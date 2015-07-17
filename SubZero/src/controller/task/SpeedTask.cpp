/*
 * SpeedTask.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: lrac
 */

#include "SpeedTask.h"
#include "FPGAInterface.h"


SpeedTask::SpeedTask(Model* fpgaModel, int targetSpeed) {
    this->fpgaModel = fpgaModel;
    this->targetSpeed = targetSpeed;
}

void SpeedTask::setTargetSpeed(int newSpeed) {
    targetSpeed = newSpeed;
}

void SpeedTask::execute() {
    if (fpgaModel != 0) {
        fpgaModel->sendCommand(SPEED, targetSpeed);
        logger->info("Speed set to " + std::to_string(targetSpeed));
    } else {
        logger->warn("Model is null");
    }
}

SpeedTask::~SpeedTask() {
    delete logger;
}

