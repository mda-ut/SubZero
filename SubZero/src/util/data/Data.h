/*
 * Data.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ahsueh1996
 */

#ifndef DATA_H_
#define DATA_H_
#include <cv.h>
#include <highgui.h>
#include <string.h>

#include <ImgData.h>
#include <FPGAData.h>


/**
 * Data is the generic class representing all data used by
 * the software to complete its tasks. Data objects will
 * each carry a ID tag that is set by the creator of it,
 * a msg that propagate details about the data. There are
 * 2 major children of data: ImgData and FPGAData which
 * hold data from the camera and the FPGA respectively.
 */
class Data {

protected:

	/* ==========================================================================
	 * VARS ACCESSIBLE BY CHILDREN
	 * ==========================================================================
	 */

	/**
	 * The ID associated to what the data is representing. This value is
	 * set by the creator of the data object.
	 */
	std::string ID;

	/**
	 * The associated message for the particular data can be recorded
	 * here.
	 */
	std::string msg;

public:
	/* ==========================================================================
	 * CONSTRUCTOR & DESTRUCTOR
	 * ==========================================================================
	 */

	/**
	 * Constructor stub.
	 */
	Data();

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
	 * Set the message carried by the data.
	 *
	 * @param newMsg 	to be set
	 * @return 			0 for success, 1 for warning that a old message was overwritten.
	 */
	int setMsg(std::string newMsg);
};

#endif /* DATA_H_ */
