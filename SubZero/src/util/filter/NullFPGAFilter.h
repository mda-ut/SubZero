/*
 * NullFPGAFilter.h
 *
 *  Created on: May 22, 2015
 *      Author: ahsueh1996
 */

#ifndef NULLFPGAFILTER_H_
#define NULLFPGAFILTER_H_

#include "Filter.h"

class NullFPGAFilter : public Filter {

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
	NullFPGAFilter();

	/**
	 * Destructor
	 */
	virtual ~NullFPGAFilter();

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
    //NullFPGAFilter* operator=(NullFPGAFilter* rhs);


	/**
	 * Copy constructor.
	 *
	 * @param obj	the reference of the new copy
	 */
	//NullFPGAFilter(NullFPGAFilter* obj);
};

#endif /* NULLFPGAFILTER_H_ */
