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

TurnTask::TurnTask(Model* fpgaModel, int& currentTargetYaw, int delta) {
    this->fpgaModel = fpgaModel;
    this->currentTargetYaw = &currentTargetYaw;
    targetYaw = currentTargetYaw + delta;
}

void TurnTask::setYawDelta(int delta) {
    setYawAbsolute(*currentTargetYaw + delta);
}

void TurnTask::setYawAbsolute(int newTargetYaw) {
    targetYaw = newTargetYaw;
}

void TurnTask::execute() {
    if (fpgaModel != 0) {
        if (targetYaw >= 180) {
           targetYaw -= 360;
         } else if (targetYaw < -180) {
           targetYaw += 360;
         }

        fpgaModel->sendCommand(YAW, targetYaw);
        *currentTargetYaw = targetYaw;
        logger->info("Target yaw set to " + std::to_string(targetYaw));
	} else {
		logger->warn("Model is null");
	}
}

TurnTask::~TurnTask() {
    delete logger;
}


