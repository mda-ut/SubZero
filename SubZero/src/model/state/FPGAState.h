/*
 * FPGAState.h
 *
 *  Created on: Feb 7, 2015
 *      Author: carl, james
 */

#ifndef FPGASTATE_H_
#define FPGASTATE_H_
#include "Observable.h"
#include "FPGAData.h"

#include <list>
#include <vector>

/**
 * FPGAState is an Observable used by FPGAModel to hold data sent from the FPGA.
 */

class FPGAState : public Observable {
private:

	//boolean to signal if a new frame has started
	bool frameStarted;

	//the length of the linked list
	//The amount of frames that the state will hold
	int maxLength;

	//Same structure as the camData,
	//LinkedList <Vector<ImgData>>
	std::list<std::vector<FPGAData>> stateData;

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
	 * Starts a new Frame
	 * Have to be called before you can call setState()
	 * Only Model should be calling this function (might implement a check for that)
	 */
	void startFrame();

	/**
	 * Ends the frame
	 * Have to be called after startFrame() is called
	 * If called before startFrame, then it does nothing
	 * Be careful when calling this, since you cannot change the frame after it has ended
	 */
	void endFrame();

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
	rawFPGA getRaw();

	/**
	 * Gets the raw FPGA data 'i' frames before this one
	 */
	rawFPGA getRaw(int t);

};

#endif /* FPGASTATE_H_ */
