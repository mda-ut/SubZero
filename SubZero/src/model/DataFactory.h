/*
 * DataFactory.h
 *
 *  Created on: Mar 17, 2015
 *      Author: ahsueh1996
 */

#ifndef DATAFACTORY_H_
#define DATAFACTORY_H_
#include "DataDefinition.h"

class DataFactory {
	/*
	 * This factory holds public functions for members of Model to
	 * create data classes as defined in DataDefinition.
	 */
public:
	// New CamData object created
	CamData createCamData(cv::Mat img, std::string ID);

	// Sister CamData object created: deep copy
	CamData createCamData(const CamData& ref);

	// New FPGAData object created
	FPGAData createFPGAData();

	// Sister FPGAData object created: deep copy
	FPGAData createFPGAData(const FPGAData& ref);
};

#endif /* DATAFACTORY_H_ */
