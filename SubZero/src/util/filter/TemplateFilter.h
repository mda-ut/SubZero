/*
 * TemplateFilter.h
 *
 *  Created on: May 22, 2015
 *      Author: ahsueh1996
 */

#ifndef TEMPLATEFILTER_H_
#define TEMPLATEFILTER_H_

#include "Filter.h"


/**
 * This filter provides a template for all other children of
 * Filter. It can also be used for testing purposes though
 * it will not do anything to a data obj.
 */
class TemplateFilter : public Filter{

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
	TemplateFilter();

	/**
	 * Destructor
	 */
	virtual ~TemplateFilter();

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
    //TemplateFilter* operator=(TemplateFilter* rhs);


	/**
	 * Copy constructor.
	 *
	 * @param obj	the reference of the new copy
	 */
    //TemplateFilter(TemplateFilter* obj);
};

#endif /* TEMPLATEFILTER_H_ */
