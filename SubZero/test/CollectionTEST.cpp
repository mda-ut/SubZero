/*
 * CollectionTEST.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: ahsueh1996
 */

#include "CollectionTEST.h"

int CollectionTEST::runDataAndFilterManagerCollection() {
	int res = 0;
    logger->trace("Running data/filter manager collection, authored by Albert");
    IDHasherTEST* hasherTest = new IDHasherTEST();
    FilterManagerTEST* filterTest = new FilterManagerTEST();
    DataTEST* dataTest = new DataTEST();
    ImgDataTEST* imgDataTest = new ImgDataTEST();
    FPGADataTEST* fpgaDataTest = new FPGADataTEST();
    logger->trace("++++++++++++++++++++++++++++++++++++");
    res += hasherTest->runUnits();
    logger->trace("++++++++++++++++++++++++++++++++++++");
    res += filterTest->runUnits();
    logger->trace("++++++++++++++++++++++++++++++++++++");
    res += dataTest->runUnits();
    logger->trace("++++++++++++++++++++++++++++++++++++");
    res += imgDataTest->runUnits();
    logger->trace("++++++++++++++++++++++++++++++++++++");
    res += fpgaDataTest->runUnits();
    logger->trace("++++++++++++++++++++++++++++++++++++");
    logger->trace(StringTools::intToStr(res)+" warning(s)");
	if (res != 0)
        logger->trace("Collection FAILED!!");
	else
        logger->trace("Collection passed");
    logger->trace("End");
	return res;
}

int CollectionTEST::runFilterCollection() {
	int res = 0;
    RGBFilterTEST* RGBFilterTest = new RGBFilterTEST();
    logger->trace("Running filter collection, authored by Albert");
    logger->trace("++++++++++++++++++++++++++++++++++++");
    res += RGBFilterTest->runUnits();
    logger->trace("++++++++++++++++++++++++++++++++++++");
    logger->trace(StringTools::intToStr(res)+" warning(s)");
	if (res != 0)
        logger->trace("Collection FAILED!!");
	else
        logger->trace("Collection passed");
    logger->trace("End");
	return res;
}
