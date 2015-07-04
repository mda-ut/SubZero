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
        fpgaModel->sendCommand(YAW, *currentYawTarget);
	} else {
		logger->warn("Model is null");
	}
}

TurnTask::~TurnTask() {
	delete logger;
}

