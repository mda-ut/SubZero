/*
 * TemplateFilter.cpp
 *
 *  Created on: May 22, 2015
 *      Author: ahsueh1996
 */

#include "TemplateFilter.h"

/* =========================================================================
 * CONSTRUCTOR AND DESTRUCTOR
 * =========================================================================
 */

TemplateFilter::TemplateFilter() : Filter() {
	this->filterID = "template";  	// initiate the generic filter type as ID
									// this ID will later be edited by filter
									// managers if the filter is to be inserted
	// initiate other class variables
}

TemplateFilter::~TemplateFilter() {
	// delete dynamic obj here. Else, leave blank
}

/* ==========================================================================
 * FILTER ACTIONS
 * ==========================================================================
 */

bool TemplateFilter::filter(Data* data) {

	// check for whether the input is of the correct type.
	Data* cast = dynamic_cast<Data*>(data);
	if (cast == 0) {
		// track the error and return error
		this->track(data,this->filterID,1,1);
        return false;
	}

	// begin filter sequence.

	// end sequence.

	// track and return
	this->track(cast,this->filterID,0,0);
    return true;
}

void TemplateFilter::setValues() {
	// provide way to set the values of the filter.
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

/*
TemplateFilter* TemplateFilter::operator =(TemplateFilter* rhs) {
	return new TemplateFilter(rhs);
}
*/
//TemplateFilter::TemplateFilter(TemplateFilter* obj) : Filter(obj) {
	/* complete as follows (note don't include filterID and msg):
	 * this->var1 = obj->var1;
	 * this->var2 = obj->var2;
	 */
//}
