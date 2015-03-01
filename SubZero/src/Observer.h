/*
 * Observable.h
 *
 *  Created on: Feb 28, 2015
 *      Author: zack.tzeng
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

/**
 * Observable is a abstract class that is made known to an observer. It contains functions to notify an observer
 * whenever changes take place.
 */
class Observer {
public:

	/**
	 * Constructor
	 */
	Observer();

	/**
	 * Destructor
	 */
	virtual ~Observer();

};

#endif /* OBSERVER_H_ */
