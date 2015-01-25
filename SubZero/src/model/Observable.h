/*
 * Observable.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

namespace std {
/**
 * Observable is a abstract class that is made known to a observer. It has a state
 * (see state) and contains functions to notify an observer whenever a state change
 * takes place.
 */
class Observable {
public:
	Observable();
	/**
	 * Constructor
	 */
	virtual ~Observable();
	/**
	 * Deconstructor
	 */
};

} /* namespace std */

#endif /* OBSERVABLE_H_ */
