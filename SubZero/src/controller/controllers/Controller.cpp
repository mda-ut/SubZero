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
    taskList = new QQueue <class Task* >;
    running = false;
}

Controller::Controller(std::vector<Model*> models_){
    models = models_;
    taskList = new QQueue <class Task* >;
}

void Controller::initialize(void) {
    cT = new ControllerThread(taskList, &mutex);
    cT->moveToThread(&queueThread);
    connect(this, &Controller::beginCT, cT, &ControllerThread::executeTasks);
    connect(cT, &ControllerThread::resultReady, this, &Controller::finished);
    connect(&queueThread, &QThread::finished, cT, &QObject::deleteLater);
    queueThread.start();
    running = true;
    emit beginCT("Begin handling Commands");
}

    //Destructor to free pointers
Controller::~Controller(){
    if(queueThread.isRunning()){
        queueThread.quit();
            queueThread.wait();
    }
    while(!taskList->isEmpty()){
        Task *temp = taskList->dequeue();
        delete temp;
    }
    delete taskList;
}

void Controller::finished(const QString &s){
    std::cout << "Bye Bye Beautiful!!" << std::endl;
}

void Controller::addTaskToQueue(Task *newTask)
{
    mutex.lock();
    taskList->enqueue(newTask);
    mutex.unlock();
}
