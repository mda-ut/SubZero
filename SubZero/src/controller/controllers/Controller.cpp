/*
 * Controller.cpp
 *
 *  Created on: Mar 12, 2015
 *      Author: ed
 */

#include "Controller.h"
#include "ControllerThread.h"
#include <iostream>

Controller::Controller(){
    taskList = *new QQueue <class Task* >;
}

Controller::Controller(std::vector<Model*> models_){
    models = models_;
    taskList = *new QQueue <class Task* >;
}

void Controller::initialize(void) {
    ControllerThread *cT = new ControllerThread(&taskList, &mutex);
    cT->moveToThread(&queueThread);
    connect(&queueThread, &QThread::finished, cT, &QObject::deleteLater);
    connect(this, &Controller::beginCT, cT, &ControllerThread::executeTasks);
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

void Controller::addTaskToQueue(Task *newTask)
{
    mutex.lock();
    taskList.enqueue(newTask);
    mutex.unlock();
}
