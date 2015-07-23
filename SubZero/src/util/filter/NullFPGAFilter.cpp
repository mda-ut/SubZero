/*
 * NullFPGAFilter.cpp
 *
 *  Created on: May 22, 2015
 *      Author: ahsueh1996
 */

#include "NullFPGAFilter.h"


/* =========================================================================
 * CONSTRUCTOR AND DESTRUCTOR
 * =========================================================================
 */

NullFPGAFilter::NullFPGAFilter() : Filter() {
	this->filterID = "NullFPGAFilter";
}

NullFPGAFilter::~NullFPGAFilter() {
	// delete dynamic obj here. Else, leave blank
}

/* ==========================================================================
 * FILTER ACTIONS
 * ==========================================================================
 */

bool NullFPGAFilter::filter(Data* data) {
	FPGAData* cast = dynamic_cast<FPGAData*>(data);

	// here we check for whether the input is of the correct type.
	if (cast == 0) {
		// track the error and return error
		this->track(data,this->filterID,1,1);
        return false;
	}
	// track and return
	this->track(cast,this->filterID,0,0);
    return true;
}

void NullFPGAFilter::setValues() {
	// provide way to set the values of the filter.
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

/*
NullFPGAFilter* NullFPGAFilter::operator =(NullFPGAFilter* rhs) {
	return new NullFPGAFilter(rhs);
}

NullFPGAFilter::NullFPGAFilter(NullFPGAFilter* obj) : Filter(obj) {
}
*/
