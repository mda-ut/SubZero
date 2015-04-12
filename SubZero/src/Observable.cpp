/*
 * Observable.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "Observable.h"


Observable::Observable() {
}

Observable::~Observable() {
	// TODO Auto-generated destructor stub
}


void Observable::addObserver(Observer* obs) {
	observers.insert(obs);
}

void Observable::removeObserver(Observer* obs) {
	observers.erase(obs);
}

void Observable::notifyObservers() {
	for (auto& obs : observers) {
		obs->update();
	}
}
