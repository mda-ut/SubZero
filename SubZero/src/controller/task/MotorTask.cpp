/*
 * MotorTask.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#include "MotorTask.h"
#include "FPGAInterface.h"

MotorTask::MotorTask() {
    // TODO Auto-generated constructor stub
}

MotorTask::MotorTask(Model* fpgaModel, bool powerOn, int& targetYaw, int& targetDepth) {
    this->fpgaModel = fpgaModel;
    this->powerOn = powerOn;
    this->targetYaw = &targetYaw;
    this->targetDepth = &targetDepth;
}

void MotorTask::execute() {
    if (fpgaModel != 0) {
        if (powerOn) {
            logger->info("Turning motor on");
            FPGAData* currentPosition = dynamic_cast<FPGAData*>(fpgaModel->getState("raw"));
            *targetDepth = currentPosition->getDepth();
            *targetYaw = currentPosition->getHeading();
            fpgaModel->sendCommand(YAW, *targetYaw);
            fpgaModel->sendCommand(DEPTH, *targetDepth);

            fpgaModel->sendCommand(MOTOR, 1);
        } else {
            logger->error("Power not on. Turn power on first.");
        }
    } else {
        logger->warn("Model is null");
    }
}

MotorTask::~MotorTask() {
    delete logger;
}
