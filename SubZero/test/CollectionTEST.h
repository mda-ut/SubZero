/*
 * CollectionTEST.h
 *
 *  Created on: Jun 3, 2015
 *      Author: ahsueh1996
 */

#ifndef TEST_COLLECTIONTEST_H_
#define TEST_COLLECTIONTEST_H_

#include"../src/util/StringTools.h"

#include "util/IDHasherTEST.h"

#include "util/filter/FilterManagerTEST.h"

#include "util/data/DataTEST.h"
#include "util/data/ImgDataTEST.h"
#include "util/data/FPGADataTEST.h"

#include "util/filter/RGBFilterTEST.h"

class CollectionTEST {
public:
	static int runDataAndFilterManagerCollection();
	static int runFilterCollection();
};

#endif /* TEST_COLLECTIONTEST_H_ */
