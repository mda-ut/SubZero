/*
 * Observable.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <stddef.h>
#include <set>
#include "Observer.h"


/**
 * Observable is a abstract class that is made known to an observer. It contains functions to notify an observer
 * whenever changes take place.
 */
class Observable {
private:
	std::set<class Observer*> observers;

public:
	/**
	 * Constructor
	 */
	Observable();

	/**
	 * Destructor
	 */
	~Observable();

	/**
	 * Attach a new observer
	 *
	 * @param obs the observer to be added to update list
	 */
	void addObserver(Observer* obs);

	/**
	 * Detach a certain observer
	 *
	 * @param obs the observer to be removed from update list
	 */
	void removeObserver(Observer* obs);

	/**
	 * Notifies observers that a new update to state is available
	 *
	 * @see Observable
	 * @see Observer
	 */
	void notifyObservers();

};

#endif /* OBSERVABLE_H_ */
