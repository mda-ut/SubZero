/*
 * CollectionTEST.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: ahsueh1996
 */

#include "CollectionTEST.h"

int CollectionTEST::runDataAndFilterManagerCollection() {
	int res = 0;
	Logger::trace("Running data/filter manager collection, authored by Albert");
	Logger::trace("++++++++++++++++++++++++++++++++++++");
	res += IDHasherTEST::runUnits();
	Logger::trace("++++++++++++++++++++++++++++++++++++");
	res += FilterManagerTEST::runUnits();
	Logger::trace("++++++++++++++++++++++++++++++++++++");
	res += DataTEST::runUnits();
	Logger::trace("++++++++++++++++++++++++++++++++++++");
	res += ImgDataTEST::runUnits();
	Logger::trace("++++++++++++++++++++++++++++++++++++");
	res += FPGADataTEST::runUnits();
	Logger::trace("++++++++++++++++++++++++++++++++++++");
	Logger::trace(StringTools::intToStr(res)+" warning(s)");
	if (res != 0)
		Logger::trace("Collection FAILED!!");
	else
		Logger::trace("Collection passed");
	Logger::trace("End");
	return res;
}

int CollectionTEST::runFilterCollection() {
	int res = 0;
	Logger::trace("Running filter collection, authored by Albert");
	Logger::trace("++++++++++++++++++++++++++++++++++++");
    res += RGBFilterTEST::runUnits();
	Logger::trace("++++++++++++++++++++++++++++++++++++");
	Logger::trace(StringTools::intToStr(res)+" warning(s)");
	if (res != 0)
		Logger::trace("Collection FAILED!!");
	else
		Logger::trace("Collection passed");
	Logger::trace("End");
	return res;
}
