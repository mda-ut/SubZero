/*
 * FPGAState.h
 *
 *  Created on: Feb 7, 2015
 *      Author: carl
 */

#ifndef FPGASTATE_H_
#define FPGASTATE_H_
#include "Observable.h"

/**
 * FPGAState is an Observable used by FPGAModel to hold data sent from the FPGA.
 * It can notify any Observers when changes are made.
 */

class FPGAState : public Observable {
private:
	double myState;

public:
	/**
	 * constructor
	 */
	FPGAState();

	/**
	 * destructor
	 */
	virtual ~FPGAState();

	double getState();
	void setState(double newState);


};

#endif /* FPGASTATE_H_ */
