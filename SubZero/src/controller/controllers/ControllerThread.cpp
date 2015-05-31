/*
 * ControllerThread.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: LuckyChewie
 */

#include "ControllerThread.h"

void ControllerThread::executeCommands() {
	QString result;
	/* ... here is the expensive or blocking operation ... */
	emit resultReady(result);
}

void ControllerThread::resultReady(const QString &s){
	//fartfartfart
}


