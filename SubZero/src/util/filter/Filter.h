/*
 * Filter.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef FILTER_H_
#define FILTER_H_
#include "DataDefinition.h"
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
	virtual int filter(CamData* camData) {
		cv::Mat temp = camData->img;
		//do filtration on temp
		free(camData);
		camData = &(new CamData(ID, temp)); // operator overload?
		return 1;
	}
	// Overload for FPGA filtering
	virtual int filter(FPGAData* fpgaData) {
		return 1;
	}

	// Get the ID of the specific filter instance
	std::string getID() {
		return ID;
	}
private:
	std::string ID;

};

#endif /* FILTER_H_ */
