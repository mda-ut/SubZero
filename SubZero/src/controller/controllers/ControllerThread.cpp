/*
 * ControllerThread.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: LuckyChewie
 */

#include "ControllerThread.h"
#include "SubZero.h"

ControllerThread::ControllerThread(QQueue<Task *> *tL, QMutex *mutex){
    taskList = tL;
    this->mutex = mutex;
}

ControllerThread::~ControllerThread() {

}

void ControllerThread::executeTasks(const QString &parameter) {
    QString result = "Done";
    while (SubZero::ctr < 5){
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
