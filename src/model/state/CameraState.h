/*
 * CameraState.h
 *
 *  Created on: Feb 7, 2015
 *      Author: carl, james
 */

#ifndef CAMERASTATE_H_
#define CAMERASTATE_H_

#include <list>
#include <vector>

#include "State.h"
#include "ImgData.h"

/**
 * CameraState is an Observable used by CameraModel to hold data sent from cameras.
 */

class CameraState : public State {

private:
    Logger* logger = new Logger("CameraState");

    //all of this class' variables are inherited from its parent (State.h)
protected:
    std::list<std::vector<ImgData*>> stateData;

public:
    /**
     * constructor
     */
    CameraState(int stateID, uint32_t bufferSize);

    /**
     * destructor
     */
    virtual ~CameraState();

    /**
     * Returns a deep copy of the image state specified with the _ID_ at _i_ frames before this call
     * @param id = id of the image that is needed
     * @param i = how many frames ago was the image stored (zero indexed; newest frame = 0)
     * @return returns the pointer to the deep copied image data
     */
    virtual ImgData* getState(std::string id, uint32_t i);

    /**
     * Returns a deep copy of the latest image specified with the _ID_
     * (same as calling getState(ID, 0))
     * @param ID = id of the image that is needed
     * @return returns the pointer to a deep copied image data
     */
    virtual ImgData* getState(std::string id);

    ImgData* getDeepState(std::string id);
    ImgData* getDeepState(std::string id, uint32_t i);

    /**
     * Sets the state
     * SHOULD ONLY BE CALLED AFTER startFrame() IS CALLED
     * @param d = Pointer to image data to be set for this frame
     * @return an int indicating whether a operation was successful
     */
    ///NO LONGER USED, USE SETSTATE WITH THE VECTOR INSTEAD
    //int setState(ImgData* d);

    /**
     * Same thing as setState, except it takes an entire vector of data instead of 1 data
     * Sets the state
     * SHOULD ONLY BE CALLED AFTER startFrame() IS CALLED
     * @param d = vector of image data to be set for this frame
     * @return an int indicating whether the operation was successful
     *  	- 0 = successful
     *  	- 1 = called this function before startFrame is called
     */
    int setState(std::vector<ImgData*> d);

    /**
     * Gets a pointer to a deep copy of the newest raw image data
     * @return a pointer to the deep copy of the raw image data
     */
    virtual ImgData* getRaw();

    /**
     * Gets a pointer to the deep copy of the raw image data _i_ frames before
     * @param i = how many frames ago the raw image was recorded (zero indexed; newest frame = 0)
     * @return a pointer to the deep copy of the raw State data _i_ frames before this function call
     */
    virtual ImgData* getRaw(uint32_t i);

};

#endif /* SRC_MODEL_STATE_CAMERASTATE_H_ */
