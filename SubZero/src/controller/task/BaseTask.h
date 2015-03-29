/*
 * BaseTask.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef BASETASK_H_
#define BASETASK_H_

class BaseTask {
public:

	//The BaseTask class is purely virtual (abstract)
	BaseTask();
	virtual ~BaseTask();

	virtual void execute()= 0;


};

#endif /* BASETASK_H_ */
