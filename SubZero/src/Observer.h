/*
 * Observer.h
 *
 *  Created on: May 4, 2015
 *      Author: ahsueh1996
 */

#ifndef SRC_OBSERVER_H_
#define SRC_OBSERVER_H_

class Observer {
public:
	Observer();
	virtual ~Observer();

	virtual void update() = 0;
};

#endif /* SRC_OBSERVER_H_ */
