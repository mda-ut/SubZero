/*
 * MoveLeftTask.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#include "MoveLeftTask.h"

MoveLeftTask::MoveLeftTask() {
	// TODO Auto-generated constructor stub
}

MoveLeftTask::MoveLeftTask(std::vector<Model*> models) {
	this->models = models;
}

void MoveLeftTask::execute() {
	if (models[0] != 0) {
		logger->info("Moving left");
		//model[0]->SENDFUNCTIONHERE
	} else {
		logger->warn("Model is null");
	}
}

MoveLeftTask::~MoveLeftTask() {
	delete logger;
}

