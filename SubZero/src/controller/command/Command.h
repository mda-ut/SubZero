/*
 * Command.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <QQueue>
#include <QMutex>

#include "../task/BaseTask.h"

class Command {
    public:
        /**
         * execute the current task
         */
        virtual void execute() = 0;

//    private:
        /**
        * A Queue of tasks each command must execute
        */
        QQueue <class BaseTask* > taskList;

        /**
         * A mutex lock that will make our writes thread safe.
         */
        QMutex mutex;

};

#endif /* COMMAND_H_ */
