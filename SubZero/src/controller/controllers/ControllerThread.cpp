/*
 * ControllerThread.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: LuckyChewie
 */

#include "ControllerThread.h"
#include <iostream>

ControllerThread::ControllerThread(QQueue <class Command* > *cL, QMutex *mutex){
    commandList = cL;
    this->mutex = mutex;
}

void ControllerThread::executeCommands(const QString &parameter) {
    QString result = "Done";
    while (1){
        mutex->lock();
        if(!commandList->isEmpty()){
            (*(commandList->dequeue())).execute();
        }
        mutex->unlock();
    }
    emit resultReady(result);
}
