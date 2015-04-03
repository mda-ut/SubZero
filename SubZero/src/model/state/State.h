#ifndef STATE_H_
#define STATE_H_
#include "Observable.h"
#include "Data.h"

#include <String>
#include <list>


class State: public Observable{

protected:
	//boolean to signal if a new frame has started
	bool frameStarted;

	//the length of the linked list
	//The amount of frames that the state will hold
	int maxLength;

	//Same structure as the camData,
	//LinkedList <Vector<ImgData>>
	std::list<vector<Data>> stateData;
public:
	State();

	virtual ~State();

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
	 * Sets the state
	 * SHOULD ONLY BE CALLED AFTER startFrame() IS CALLED
	 * OR ELSE IT WOULD THROW FrameNotStartedException
	 * @param image data to be set for this frame
	 * @throws FrameNotStartedException
	 */
	void setState(Data d);

	/**
	 * Same thing as setState, except it takes an entire vector of data instead of 1 data
	 * Sets the state
	 * SHOULD ONLY BE CALLED AFTER startFrame() IS CALLED
	 * OR ELSE IT WOULD THROW FrameNotStartedException
	 * @param vector of image data to be set for this frame
	 * @throws FrameNotStartedException
	 */
	void setStates(std::vector<Data> d);

	/**
	 * Returns a deep copy of an image specified with the _id_ at _t_ frames before this call
	 * @param id = id of the image that is needed
	 			t = how many frames ago was the image stored
	 */
	Data getState (std::String id, int t);

	/**
	 * Returns a deep copy of the latest image specified with the _id_
	 * (same as calling getImage(id, 0))
	 * @param id = id of the image that is needed
	 */
	Data getState (std::String id);

	/**
	 * Gets the newest raw image
	 */
	Data getRaw();

	/**
	 * Gets the raw image _t_ frames before
	 */
	Data getRaw(int t);

};

#endif /* SRC_MODEL_STATE_STATE_H_ */
