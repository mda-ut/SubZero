/*
 * Task.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Task.h"

Task::~Task() {
    for(int i = 0 ; i < taskList.size() ; i++) {
        delete taskList[i];
    }
}
