/*
 * CommandCCR.h
 *
 *  Created on: Jun 6, 2015
 *      Author: LuckyChewie
 *
 *  This is a dummy Command that we used on Jun 6 for testing.
 *  The idea was to display on stdout the Creedence Clearwater Revival (CCR) lyric - "Hey, Tonight!"
 */

#ifndef TASKCCR_H
#define TASKCCR_H

#include "Task.h"

class TaskCCR : public Task {
public:
        TaskCCR();

        ~TaskCCR();

        virtual void execute();
};

#endif // TASKCCR_H
