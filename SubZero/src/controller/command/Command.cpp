/*
 * Command.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Command.h"

Command Command::(BaseTask *inputTask) {
	currentTask = inputTask;
}

Command::~Command() {
	// TODO Auto-generated destructor stub
}

void Command:: execute(){}

