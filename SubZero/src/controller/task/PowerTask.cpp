/*
 * PowerTask.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#include "PowerTask.h"
#include "FPGAInterface.h"

PowerTask::PowerTask(Model* fpgaModel) {
    this->fpgaModel = fpgaModel;
}

void PowerTask::execute() {
    if (fpgaModel != 0) {
        FPGAData* fpga = dynamic_cast<FPGAData*>(fpgaModel->getStateData("raw"));
        int power = fpga->getPower();
        if (!power) {
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
