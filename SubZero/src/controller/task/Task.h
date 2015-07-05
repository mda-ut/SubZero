/*
 * Task.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef TASK_H_
#define TASK_H_

#include <QMutex>
#include <vector>
#include "Model.h"

#define POOL_SURFACE_HEIGHT 300

class Task {
    public:
        //The Task class is purely virtual (abstract)
        virtual ~Task();

        virtual void execute() = 0;

    protected:
       std::vector<Task*> taskList;
};

#endif /* TASK_H_ */
