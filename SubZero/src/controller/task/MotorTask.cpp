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

MotorTask::MotorTask(Model* fpgaModel){
    this->fpgaModel = fpgaModel;
}

void MotorTask::execute() {
    if (fpgaModel != 0) {
        FPGAData* currentPosition = dynamic_cast<FPGAData*>(fpgaModel->getStateData("raw"));
        bool powerOn = currentPosition->getPower();
        if (powerOn) {
            logger->info("Turning motor on");
            int targetDepth = currentPosition->getDepth();
            int targetYaw = currentPosition->getYaw();
            fpgaModel->sendCommand(YAW, targetYaw);
            fpgaModel->sendCommand(DEPTH, targetDepth);
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
