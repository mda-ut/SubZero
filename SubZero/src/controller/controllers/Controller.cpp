/*
 * Controller.cpp
 *
 *  Created on: Mar 12, 2015
 *      Author: ed
 */

#include "Controller.h"
#include "ControllerThread.h"
//
//Controller::Controller(std::vector <Model*> model){
//    ControllerThread *cT = new ControllerThread();
//    cT->moveToThread(&queueThread);
//	connect(&queueThread, &QThread::finished, cT, &QObject::deleteLater);
//	connect(this, &Controller::beginCT, cT, &ControllerThread::executeCommands);
//	connect(cT, &ControllerThread::resultReady, this, &Controller::cTHandleResults);
//	queueThread.start();
//}
//
//    //Destructor to free pointers
//Controller::~Controller(){
//
//}
//
//void Controller::cTHandleResults(const QString &){}
//
