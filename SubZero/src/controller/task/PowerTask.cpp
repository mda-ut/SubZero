/*
 * PowerTask.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#include "PowerTask.h"
#include "FPGAInterface.h"

PowerTask::PowerTask() {
    // TODO Auto-generated constructor stub
}

PowerTask::PowerTask(Model* fpgaModel, bool powerOn) {
    this->fpgaModel = fpgaModel;
    this->powerOn = powerOn;
}

void PowerTask::execute() {
    if (fpgaModel != 0) {
        if (powerOn) {
            logger->info("Turning power on");
            fpgaModel->sendCommand(POWER, 1);
        } else {
            logger->info("Turning power off");
            fpgaModel->sendCommand(POWER, 0);
        }
    } else {
        logger->warn("Model is null");
    }
}

PowerTask::~PowerTask() {
    delete logger;
}
