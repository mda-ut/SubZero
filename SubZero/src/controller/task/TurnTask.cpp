/*
 * TurnTask.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#include "TurnTask.h"
#include "FPGAInterface.h"

TurnTask::TurnTask() {
	// TODO Auto-generated constructor stub
}

TurnTask::TurnTask(Model* fpgaModel, int& currentYawTarget, int delta) {
    this->fpgaModel = fpgaModel;
    this->currentYawTarget = &currentYawTarget;
    this->delta = delta;
}

void TurnTask::execute() {
    if (fpgaModel != 0) {
		logger->info("Moving left");

        *currentYawTarget += delta;
        if (*currentYawTarget >= 180) {
           *currentYawTarget -= 360;
         } else if (*currentYawTarget < -180) {
           *currentYawTarget += 360;
         }

        fpgaModel->sendCommand(YAW, *currentYawTarget);
        logger->info("Target yaw set to " + std::to_string(*currentYawTarget));
	} else {
		logger->warn("Model is null");
	}
}

TurnTask::~TurnTask() {
	delete logger;
}

