/*
 * Data.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ahsueh1996
 */

#ifndef DATA_H_
#define DATA_H_

#include <cv.h>
#include <opencv2/highgui.hpp>
#include <string.h>
#include "../StringTools.h"

#include "../Logger.h"

/**
 * Data is the generic class representing all data used by
 * the software to complete its tasks. Data objects will
 * each carry a ID tag that is set by the creator of it,
 * a msg that propagate details about the data. There are
 * 2 major children of data: ImgData and FPGAData which
 * hold data from the camera and the FPGA respectively.
 */
class Data {

	/* =========================================================================
	 * FRIEND CLASSES
	 * =========================================================================
	 */
	friend class Filter;
	friend class HwInterface;

protected:

	/* ==========================================================================
	 * VARS ACCESSIBLE BY CHILDREN
	 * ==========================================================================
	 */

	/**
	 * The ID associated to what the data is representing. This value is
	 * set by the creator of the data object.
	 */
	std::string dataID;

	/**
	 * The associated message for the particular data can be recorded
	 * here.
	 */
	std::string msg;

	/*
	 * Tracks the things that changed the data. Usually tracks which filters were applied to the image.
	 */
	std::string tracker;

	/* ==========================================================================
	 * FUNC ACCESSIBLE BY CHILDREN
	 * ==========================================================================
	 */

	/**
	 * Adds a task to the tracker string according to a set standard (defined
	 * in cpp).
	 *
	 * @param task	is the action done to the data which needs to be tracked.
	 * @param error	is the result of the action if applicable.
	 * @param type	is the switch to track error or not. 1 for yes, 0 for no.
	 */
	void track(std::string task, int error, int type);

	/**
	 * Resets the tracker string to empty.
	 */
	void resetTracker();

public:
	/* ==========================================================================
	 * CONSTRUCTOR & DESTRUCTOR
	 * ==========================================================================
	 */

	/**
	 * Constructor stub.
	 *
	 * @param dataID	identifies what the data represents
	 */
	Data(std::string dataID);

	/**
	 * Destructor stub.
	 */
	virtual ~Data();

	/* ==========================================================================
	 * PUBLIC FUNCS COMMON TO ALL CHILDREN
	 * ==========================================================================
	 */

	/**
	 * Getter for the data object's ID
	 *
	 * @return return the string ID of the data
	 */
	std::string getID();

	/**
	 * Getter for the message stored within the data.
	 *
	 * @return string message
	 */
	std::string getMsg();

	/**
	 * Set the ID of data.
	 *
	 * @param newID		to be set
	 */
	void setID(std::string newID);

	/**
	 * Set the message carried by the data.
	 *
	 * @param newMsg 	to be set
	 * @return 			0 for success, 1 for warning that a old message was overwritten.
	 */
	int setMsg(std::string newMsg);

	/**
	 * Appends a new message to the original message.
	 *
	 * @param newMsg 	to be appended
	 */
	void addMsg(std::string newMsg);

	/**
	 * Return the track record of the data.
	 *
	 * @return		String representing the history of the img's filtration.
	 */
	std::string getTrack();

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */

	/**
	 * The = operator overload that will complete a deep copy of the
	 * right hand side operator and return it. This generic operator
	 * overload casts into the correct Data operator overload
	 *
	 * @param rhs	the right hand side of the equal operator, the parent copy
	 * @return		address to a new Data
	 */
	Data* operator=(Data* rhs);

	/**
	 * Copy constructor
	 *
	 * @param obj	the object referenced in the construction
	 */
	Data(const Data* obj);
};

#endif /* DATA_H_ */
