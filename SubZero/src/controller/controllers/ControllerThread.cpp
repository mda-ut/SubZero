/*
 * ControllerThread.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: LuckyChewie
 */

#include "ControllerThread.h"

ControllerThread::ControllerThread(QQueue<Task *> *tL, QMutex *mutex){
    taskList = tL;
    this->mutex = mutex;
}

void ControllerThread::executeTasks(const QString &parameter) {
    QString result = "Done";
    while (1){
        mutex->lock();
        if(!taskList->isEmpty()){
            Task *temp = taskList->dequeue();
            temp->execute();
            delete temp;
        }
        mutex->unlock();
    }
    emit resultReady(result);
}
