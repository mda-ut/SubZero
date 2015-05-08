/*
 * DataFactory.h
 *
 *  Created on: Mar 17, 2015
 *      Author: ahsueh1996
 */

#ifndef DATAFACTORY_H_
#define DATAFACTORY_H_
#include "Data.h"
#include "FPGAData.h"
#include "ImgData.h"

/**
 * This factory holds public functions for members of Model to
 * create data classes as defined in Data.h.
 */
class DataFactory {

public:
	/**
	 * New CamData object created. Takes the data required by
	 * ImgData and returns a ImgData*.
	 *
	 * @param imgID	of the image
	 * @param Mat 	pointer of the actual image object
	 * @return 		pointer to the newly made ImgData obj
	 */
	static ImgData* createImgData(std::string imgID, cv::Mat* img);

	/*
	 * New FPGAData object created. Takes the data required by
	 * FPGAData and returns a FPGAData*.
	 *
	 * @param fpgaID	of the fpga data point
	 * @param depth
	 * @param roll
	 * @param heading
	 * @return 			pointer to the newly made FPGAData obj.
	 */
	static FPGAData* createFPGAData(std::string fpgaID, double depth, double roll, double heading);
};

#endif /* DATAFACTORY_H_ */
