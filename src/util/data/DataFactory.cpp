/*
 * DataFactory.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: ahsueh1996
 */

#include "DataFactory.h"

Data* DataFactory::createData(std::string dataID) {
	return new Data(dataID);
}

ImgData* DataFactory::createImgData(std::string imgID, cv::Mat img) {
	return new ImgData(imgID,img);
}

FPGAData* DataFactory::createFPGAData(std::string fpgaID, double depth,
		double roll, double heading) {
	return new FPGAData(fpgaID,depth,roll,heading);
}
