/*
 * NullImgFilter.cpp
 *
 *  Created on: May 22, 2015
 *      Author: ahsueh1996
 */

#include "NullImgFilter.h"

/* =========================================================================
 * CONSTRUCTOR AND DESTRUCTOR
 * =========================================================================
 */

NullImgFilter::NullImgFilter() : Filter() {
	this->filterID = "NullImgFilter";
}

NullImgFilter::~NullImgFilter() {
	// delete dynamic obj here. Else, leave blank
}

/* ==========================================================================
 * FILTER ACTIONS
 * ==========================================================================
 */

bool NullImgFilter::filter(Data* data) {
	// here we check for whether the input is of the correct type.
	ImgData* cast = dynamic_cast<ImgData*>(data);
	if (cast == 0) {
		// track the error and return error
		this->track(data,this->filterID,1,1);
        return false;
	}
	// track and return
	this->track(cast,this->filterID,0,0);
    return true;
}

void NullImgFilter::setValues() {
	// provide way to set the values of the filter.
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

/*
NullImgFilter* NullImgFilter::operator =(NullImgFilter* rhs) {
	return new NullImgFilter(rhs);
}

NullImgFilter::NullImgFilter(NullImgFilter* obj) : Filter(obj) {
}
*/
