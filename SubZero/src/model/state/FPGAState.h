/*
 * FPGAState.h
 *
 *  Created on: Feb 7, 2015
 *      Author: carl, james
 */

#ifndef FPGASTATE_H_
#define FPGASTATE_H_
#include "Observable.h"
#include "State.h"
#include "FPGAData.h"

#include <list>
#include <vector>
#include <String>

/**
 * FPGAState is an Observable used by FPGAModel to hold data sent from the FPGA.
 */

class FPGAState : public State, public Observable {

	//all of this class' variables are inherited from its parent (State.h)

public:
	/**
	 * constructor
	 */
	FPGAState();

	/**
	 * destructor
	 */
	virtual ~FPGAState();

	/**
	 * Gets the most recent fpga state
	 * (Need discussion on whether FPGA data will need an ID)
	 */
	FPGAData getState();

	/**
	 * Gets the fpga state _t_ frames before
	 */
	FPGAData getState(int t);

	/**
	 * Sets the fpga state
	 * Should be called once every frame
	 */
	void setState(FPGAData state);

	/**
	 * Gets the most recent raw FPGA data
	 */
	FPGAData getRaw();

	/**
	 * Gets the raw FPGA data 'i' frames before this one
	 */
	FPGAData getRaw(int t);
};

#endif /* FPGASTATE_H_ */
