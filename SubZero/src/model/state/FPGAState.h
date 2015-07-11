/*
 * FPGAState.h
 *
 *  Created on: Feb 7, 2015
 *      Author: carl, james
 */

#ifndef FPGASTATE_H_
#define FPGASTATE_H_
#include "State.h"
#include "FPGAData.h"

/**
 * FPGAState is an Observable used by FPGAModel to hold data sent from the FPGA.
 */

class FPGAState : public State {

private:
    Logger* logger;

    //all of this class' variables are inherited from its parent (State.h)
protected:
    std::list<std::vector<FPGAData*>> stateData;

public:
    /**
     * constructor
     */
    FPGAState(int stateID);
    FPGAState(int stateID, int framesStored);

    /**
     * destructor
     */
    virtual ~FPGAState();

    /**
     * Returns a deep copy of the FPGA data specified with the _ID_ at _i_ frames before this call
     * @param id = id of the FPGA data that is needed
     * @param i = how many frames ago was the FPGA data was stored (zero indexed; newest frame = 0)
     * @return returns the pointer to a deep copied FPGA data
     */
    FPGAData* getState (std::string id, int i);

    /**
     * Returns a deep copy of the newest FPGA data specified with the _ID_
     * @param id = id of the FPGA data that is needed
     * @return returns the pointer to a deep copied FPGA data
     */
    FPGAData* getState (std::string id);

    /**
     * Sets the FPGA state
     * SHOULD ONLY BE CALLED AFTER startFrame() IS CALLED
     * @param d = Pointer to FPGA data to be set for this frame
     * @return an int indicating whether the operation was successful
     *  	- 0 = successful
     *  	- 1 = called this function before startFrame is called
     */
    //int setState(FPGAData* d);

    /**
     * Same thing as setState, except it takes an entire vector of FPGA data instead of 1 data
     * Sets the FPGA state
     * SHOULD ONLY BE CALLED AFTER startFrame() IS CALLED
     * @param d = vector of FPGA data to be set for this frame
     * @return an int indicating whether the operation was successful
     *  	- 0 = successful
     *  	- 1 = called this function before startFrame is called
     */
    int setState(std::vector<FPGAData*> d);

    /**
     * Gets a pointer to a deep copy of the newest raw FPGA data
     * @param data = pointer to the deep copy of the raw FPGA data
     */
    FPGAData* getRaw();

    /**
     * Gets a pointer to the deep copy of the raw FPGA data _i_ frames before
     * @param i = how many frames ago the raw FPGA data was recorded (zero indexed; newest frame = 0)
     * @param data = pointer to the deep copy of the raw FPGA data _i_ frames before this function call
     * @return returns an int to indicate if the operation was successful
     * 		- 0 = success
     * 		- 1 = index out of range
     */
    FPGAData* getRaw(int i);

};

#endif /* FPGASTATE_H_ */
