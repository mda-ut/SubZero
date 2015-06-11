/*
 * CommandCCR.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: LuckyChewie
 *
 */

#include "CommandCCR.h"

#include "../task/TaskA.h"
#include "../task/TaskHeyTonight.h"

#include <iostream>

CommandCCR::CommandCCR()
{
    taskList = *new QQueue <class BaseTask* >;

    TaskA *Lodi = new TaskA;
    TaskHeyTonight *GreenRiver = new TaskHeyTonight;

    mutex.lock();
    taskList.enqueue(Lodi);
    taskList.enqueue(GreenRiver);
    mutex.unlock();

}

void CommandCCR::execute(){
    while (!taskList.isEmpty()){
        mutex.lock();
        (taskList.dequeue())->execute();
        mutex.unlock();
    }
    return;
}
