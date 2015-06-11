/*
 * Controller.cpp
 *
 *  Created on: Mar 12, 2015
 *      Author: ed
 */

#include "Controller.h"
#include "ControllerThread.h"

#include <iostream>

Controller::Controller(void){
    commandList = *new QQueue <class Command* >;
}

void Controller::initialize(void) {
    ControllerThread *cT = new ControllerThread(&commandList, &mutex);
    cT->moveToThread(&queueThread);
    connect(&queueThread, &QThread::finished, cT, &QObject::deleteLater);
    connect(this, &Controller::beginCT, cT, &ControllerThread::executeCommands);
    connect(cT, &ControllerThread::resultReady, this, &Controller::cTHandleResults);
    queueThread.start();
    emit beginCT("Begin handling Commands");
}

    //Destructor to free pointers
Controller::~Controller(){
    queueThread.quit();
    queueThread.wait();
}

void Controller::cTHandleResults(const QString &s){
    std::cout << "Bye Bye Beautiful!!" << std::endl;
}

void Controller::addCommandToQueue(Command *newCommand)
{
    mutex.lock();
    commandList.enqueue(newCommand);
    mutex.unlock();
}
