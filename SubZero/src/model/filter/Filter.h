/*
 * Filter.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef FILTER_H_
#define FILTER_H_
#include "dataDefinition.h"

// Include all different children of Filter class.
#include "RGBFilter.h"
//#include "HSVFilter.h"


class Filter {
	/*
	 * Filter is a virtual class that is further specified into specific
	 * filters accessible by FilterFactory. In general filters will have
	 * a filter() function that will filter input according to the
	 * algorithm it contains and the parameters it holds.
	 */

public:
	Filter();
	virtual ~Filter();

	// The filter function takes a pointer and applies the algorithm of the
	// specific filter to the content of the pointer. The content of the
	// pointer is altered and 0 is returned for successful filter, 1 for no
	// action performed due to incorrect type, 2 for other errors.
	virtual int filter(CamData * inputImg) {
		return 1;
	}
	// Overload for FPGA filtering
	virtual int filter(FPGAData * inputAttitude) {
		return 1;
	}
};

#endif /* FILTER_H_ */
