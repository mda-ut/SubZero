/*
 * ControllerThread.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: LuckyChewie
 */

#include "ControllerThread.h"
#include "Controller.h"

ControllerThread::ControllerThread(QQueue<Task *> *tL, QMutex *mutex){
    taskList = tL;
    this->mutex = mutex;
}

ControllerThread::~ControllerThread() {
    delete logger;
}

void ControllerThread::executeTasks(const QString &parameter) {
    QString result = "Done";
    logger->info("Starting Controller Thread execution loop");
    while (Controller::isRunning()){
        mutex->lock();
        if(!taskList->isEmpty()){
            Task *temp = taskList->dequeue();
            logger->trace("Executing new task");
            temp->execute();
            delete temp;
        }
        mutex->unlock();
    }
    emit resultReady(result);
}
