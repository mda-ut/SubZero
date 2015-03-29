/*
 * TaskA.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ed
 */

#ifndef SUBZERO_SRC_CONTROLLER_TASK_TASKA_H_
#define SUBZERO_SRC_CONTROLLER_TASK_TASKA_H_

class TaskA : public BaseTask {
public:
	TaskA();
	virtual ~TaskA();

    virtual void execute();
};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_TASKA_H_ */
