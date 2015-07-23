/*
 * NullImgFilter.h
 *
 *  Created on: May 22, 2015
 *      Author: ahsueh1996
 */

#ifndef NULLIMGFILTER_H_
#define NULLIMGFILTER_H_

#include "Filter.h"

class NullImgFilter : public Filter {

private:
	/* =========================================================================
	 * CLASS VARS USED FOR FILTRATION
	 * =========================================================================
	 */

public:
	/* =========================================================================
	 * CONSTRUCTOR AND DESTRUCTOR
	 * =========================================================================
	 */

	/**
	 * Constructor
	 */
	NullImgFilter();

	/**
	 * Destructor
	 */
	virtual ~NullImgFilter();

	/* ==========================================================================
	 * FILTER ACTIONS
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
    bool filter(Data* data);

	/**
	 * Sets the values defined in the CLASS VARS section.
	 */
	void setValues();

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */

	/**
	 * Operator = overload
	 *
	 * @param rhs	the filter obj on the right hand side of the = operator
	 * @return 		pointer to the new deep copy of rhs
	 */
    //NullImgFilter* operator=(NullImgFilter* rhs);


	/**
	 * Copy constructor.
	 *
	 * @param obj	the reference of the new copy
	 */
    //NullImgFilter(NullImgFilter* obj);
};

#endif /* NULLIMGFILTER_H_ */
