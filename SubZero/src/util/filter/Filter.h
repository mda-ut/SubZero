/*
 * Filter.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef FILTER_H_
#define FILTER_H_
#include "../data/Data.h"
#include "../data/ImgData.h"
#include "../data/FPGAData.h"

/**
 * Filter is a virtual class that is further specified into specific
 * filters accessible by FilterFactory. In general filters will have
 * a filter function that will filter input according to the
 * algorithm it contains and the parameters it holds thus overriding
 * the virtual filter() of this parent class.
 */
class Filter {

	protected:
	/* ==========================================================================
	 * CLASS VARIABLES
	 * Theses variables are accessible by children of Filter class.
	 * ==========================================================================
	 */

	/*
	 * Identifier for the filter.
	 */
	std::string filterID;

	/*
	 * Message propagated by the filter.
	 */
	std::string msg;

public:
	/* =========================================================================
	 * CONSTRUCTOR AND DESTRUCTOR
	 * =========================================================================
	 */

	/**
	 * Constructor
	 */
	Filter();

	/**
	 * Destructor
	 */
	virtual ~Filter();

	/* ==========================================================================
	 * METHODS
	 * Inherent to all filters
	 * ==========================================================================
	 */


	/**
	 * The filter function takes a pointer and applies the algorithm of the
	 * specific filter to the content of the pointer. The content of the
	 * pointer is altered.
	 *
	 * @param data 	to be processed
	 * @return 		0 for success 1 for incorrect type.
	 */
	virtual int filter(Data* data);

	/**
	 * Get the ID of the specific filter instance
	 *
	 * @return string of ID.
	 */
	std::string getID();

	/**
	 * Set ID of a filter.
	 *
	 * @param filterID	is the identifier of the Filter object.
	 * return 			0 for success, 1 for fail.
	 */
	int setID(std::string ID);

	/**
	 * Get the msg of the filter object.
	 *
	 * @return msg		return the msg stored by the object.
	 */
	std::string getMsg();

	/**
	 * Set a msg to a filter object.
	 *
	 * @param msg 	to be propagated.
	 * @return 		0 for normal operation, 1 for warning of overwrite operation.
	 */
	int setMsg();
};

#endif /* FILTER_H_ */
