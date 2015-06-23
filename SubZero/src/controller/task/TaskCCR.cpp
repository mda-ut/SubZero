/*
 * CommandCCR.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: LuckyChewie
 *
 */

#include "TaskCCR.h"

#include "../task/TaskHelloWorld.h"
#include "../task/TaskHeyTonight.h"

#include <iostream>

TaskCCR::TaskCCR()
{
    taskList = *new std::vector <class Task* >();

    TaskHelloWorld *Lodi = new TaskHelloWorld();
    TaskHeyTonight *LookingOutMyBackDoor = new TaskHeyTonight();

    taskList.push_back(Lodi);
    taskList.push_back(LookingOutMyBackDoor);
}

TaskCCR::~TaskCCR()
{
    int i = 0;
    for( ; i < taskList.size() ; i++){
        delete taskList[i];
    }
}

void TaskCCR::execute(){
    taskList[0]->execute();
    taskList[1]->execute();
    return;
}
