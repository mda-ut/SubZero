/*
 * ControllerThread.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: LuckyChewie
 */

#include "ControllerThread.h"

void ControllerThread::run() Q_DECL_OVERRIDE {
	QString result;
	/* ... here is the expensive or blocking operation ... */
	emit resultReady(result);
}
/*void ControllerThread::resultReady(const QString &s){
	//fartfartfart
}
*/

