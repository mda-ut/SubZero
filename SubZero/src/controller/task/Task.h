/*
 * BaseTask.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef TASK_H_
#define TASK_H_

#include <QMutex>
#include <vector>

//View adding QObject to allow QObject * version of signal mapping


#define TASKLISTLENGTH 10

class Task{

    public:
        //The Task class is purely virtual (abstract)
        virtual ~Task();

        virtual void execute() = 0;

    protected:
       std::vector <Task*> taskList;
};

#endif /* BASETASK_H_ */
