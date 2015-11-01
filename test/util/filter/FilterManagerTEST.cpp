/*
 * FilterManagerTEST.cpp
 *
 *  Created on: May 19, 2015
 *      Author: ahsueh1996
 */

#include "FilterManagerTEST.h"

/* TEMPLATE
	int fail = 0;
    logger->trace("==============================");

	if (fail > 0)
        logger->warn("  TEST FAILED: _______");
    logger->trace("==============================");
	return fail;
 */

int FilterManagerTEST::runUnits() {
    int res = 0;

    logger->trace("Running all unit tests for: FilterManager");
    logger->trace("==============================");
	res += T_Constructor();
	res += T_applyFilterChain();
	res += T_insertFilter();
	res += T_replaceFilter();
    logger->trace("==============================");
	if (res != 0)
        logger->warn(StringTools::intToStr(res)+" warning(s) in unit tests");
    logger->trace("Unit testing complete: FilterManager");
    logger->trace("NOTE: all units mem tested");
	return res;
}

/* ==========================================================================
 * CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */

int FilterManagerTEST::T_Constructor() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing FilterManager constructor:");
    logger->trace(" Constructing normal mode fm under ID \"normal fm\"...");
	FilterManager* fm = new FilterManager("normal fm");
    logger->trace("  Complete.");
    logger->trace(" Accessing initialized parameters...");
    logger->trace("  Using getFMID()...");
    logger->trace("    "+fm->getFMID());
	if (fm->getFMID() == "normal fm")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, fmID incorrect");
		fail++;
	}
    logger->trace("  Using getCount()...");
    logger->trace("    "+StringTools::intToStr(fm->getSizeOfFilterChain()));
	if (fm->getSizeOfFilterChain() == 0)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, size of filter chain not 0");
		fail++;
	}
    logger->trace("  Using getMode()...");
	if (fm->getMode() == 0)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok: Mode incorrect");
		fail += 1;
	}
    logger->trace("  Complete.");
    logger->trace(" Deleting \"normal fm\"...");
	delete fm;
    logger->trace(" Constructing normal mode fm under ID \"auto fm\"...");
	fm = new FilterManager("auto fm",1);
    logger->trace("  Complete.");
    logger->trace(" Accessing initialized parameters...");
    logger->trace("  Using getFMID()...");
    logger->trace("    "+fm->getFMID());
	if (fm->getFMID() == "auto fm")
            logger->trace("    ok");
	else {
        logger->warn("    NOT ok, fmID incorrect");
		fail++;
	}
    logger->trace("  Using getCount()...");
    logger->trace("    "+StringTools::intToStr(fm->getSizeOfFilterChain()));
	if (fm->getSizeOfFilterChain() == 0)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, size of filter chain not 0");
		fail++;
	}
    logger->trace("  Using getMode()...");
	if (fm->getMode() == 1)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok: Mode incorrect");
		fail += 1;
	}
    logger->trace("  Complete.");
	delete fm;
    logger->trace("Testing complete.");

	if (fail > 0)
        logger->warn("  TEST FAILED: FilterManager constructor");
    logger->trace("==============================");
	return fail;
}

int FilterManagerTEST::T_Destructor() {
    return 0;
}

/* ==========================================================================
 * MAIN FUNCTIONALITY: FILTRATION
 * ==========================================================================
 */

int FilterManagerTEST::T_applyFilterChain() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing applyFilterChain():");
    logger->trace(" Creating FM under normal mode...");
	FilterManager* fm = new FilterManager("fm");
    logger->trace(" Using factory, making 4 random filters...");
	Filter* f1,*f2,*f3,*f4;
	f1 = FilterFactory::createFilter();
	f2 = FilterFactory::createNullImgFilter();
	f3 = FilterFactory::createNullFPGAFilter();
	f4 = FilterFactory::createFilter();
    logger->trace(" Inserting f1 as \"task 3\" to FRONT...");
	fm->insertFilter("task 3",f1,"FRONT");
    logger->trace(" Inserting f2 as \"task 1\"...");
	fm->insertFilter("task 1",f2,"task 3");
    logger->trace(" Inserting f3 as \"task 2\" between f1,f2...");
	fm->insertFilter("task 2",f3,"task 3");
    logger->trace(" Inserting f4 as \"task 4\" to REAR...");
	fm->insertFilter("task 4",f4);
    logger->trace(" Making img objs...");
	cv::Mat img = cv::Mat::zeros(2,2,CV_8UC1);
    ImgData* data = new ImgData("input",img);
    logger->trace(" Applying all filters...");
	int res = fm->applyFilterChain(data);
    logger->trace("  Checking data ID...");
    logger->trace("    "+data->getID());
	if (data->getID() == "fm")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, ID not set!");
		fail++;
	}
    logger->trace("    "+data->getTrack()+"error code "+StringTools::intToStr(res));
	if (data->getTrack() == "task 1; task 2-1; task 3; task 4; ")
		if (res == 1)
            logger->trace("    ok");
		else {
            logger->warn("    NOT ok, error code incorrect");
		}
	else {
        logger->warn("    NOT ok, track record not expected");
	}
    img.release();
    delete data;
    delete fm;
    logger->trace("Testing complete.");

	if (fail > 0)
        logger->warn("  TEST FAILED: applyFilterChain");
    logger->trace("==============================");
	return fail;
}

/* ==========================================================================
 * FILTER MANAGMENT FUNCTIONS: CUSTOM ID MODE and AUTO ID MODE
 * ==========================================================================
 */

int FilterManagerTEST::T_insertFilter() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing insertFilter():");
    logger->trace(" Test under custom ID mode...");
	FilterManager* fm = new FilterManager("fm");
    logger->trace("  Using factory, making 4 general filters...");
	Filter* f1,*f2,*f3,*f4,*f5;
	f1 = FilterFactory::createFilter();
	f2 = FilterFactory::createFilter();
	f3 = FilterFactory::createFilter();
	f4 = FilterFactory::createFilter();
	f5 = FilterFactory::createFilter();
    logger->trace("  Inserting f1 as \"task 3\" to FRONT...");
	fm->insertFilter("task 3",f1,"FRONT");
    logger->trace("  Inserting f2 as \"task 1\"...");
	fm->insertFilter("task 1",f2,"task 3");
    logger->trace("  Inserting f3 as \"task 2\" between f1,f2...");
	fm->insertFilter("task 2",f3,"task 3");
    logger->trace("  Inserting f4 as \"task 4\" to REAR...");
	fm->insertFilter("task 4",f4);
    logger->trace("  Using getFilterChainIDs()...");
	std::vector<std::string> list = fm->getFilterChainIDs();
	std::string res;
	for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+*it;
    logger->trace("   "+res);
	if (res == " task 1 task 2 task 3 task 4")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, list unexpected");
		fail += 1;
	}
    logger->trace("  Try inserting w/ non unique ID...");
	res = StringTools::intToStr(fm->insertFilter("task 2",f5));
    logger->trace("    error code: "+res);
	if (res == "2")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, incorrect error");
		fail += 1;
	}
    logger->trace("  Try inserting out of range...");
	res = StringTools::intToStr(fm->insertFilter("task 2",f5,"what task?"));
    logger->trace("    error code: "+res);
	if (res == "1")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, incorrect error");
		fail += 1;
	}
    logger->trace("  Try inserting with no filterID arg...");
	res = StringTools::intToStr(fm->insertFilter(f5,"Task 2"));
    logger->trace("    error code: "+res);
	if (res == "4")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, incorrect error");
		fail += 1;
	}
	delete f5;
	delete fm;

    logger->trace(" Test under auto ID mode...");
	fm = new FilterManager("fm",1);
    logger->trace("  Using factory, making 4 general filters...");
	f1 = FilterFactory::createFilter();
	f2 = FilterFactory::createFilter();
	f3 = FilterFactory::createFilter();
	f4 = FilterFactory::createFilter();
	f5 = FilterFactory::createFilter();
    logger->trace("  Inserting f1 to FRONT...");
	fm->insertFilter(f1,"FRONT");
    logger->trace("  Inserting f2...");
	fm->insertFilter(f2);
    logger->trace("  Inserting f3 between f1,f2...");
	fm->insertFilter(f3,"2 GenericFilter");
    logger->trace("  Inserting f4 to REAR...");
	fm->insertFilter(f4,"REAR");
	res = "";
    logger->trace("  Using getFilterChainIDs()...");
	list = fm->getFilterChainIDs();
	for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+*it;
    logger->trace("   "+res);
	if (res == " 1 GenericFilter 3 GenericFilter 2 GenericFilter 4 GenericFilter")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, list unexpected");
		fail += 1;
	}
    logger->trace("  Try inserting w/ custom ID...");
	res = StringTools::intToStr(fm->insertFilter("task 2",f5));
    logger->trace("    error code: "+res);
	if (res == "0")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, incorrect error");
		fail += 1;
	}
    logger->trace("  Try inserting out of range...");
	res = StringTools::intToStr(fm->insertFilter(f5,"what task?"));
    logger->trace("    error code: "+res);
	if (res == "1")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, incorrect error");
		fail += 1;
	}
    logger->trace("Testing complete.");
    delete fm;

	if (fail > 0)
        logger->warn("  TEST FAILED: insertFilter()");
    logger->trace("==============================");
	return fail;
}

int FilterManagerTEST::T_replaceFilter() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("Testing replaceFilter():");
    logger->trace(" Test under custom ID mode...");
	FilterManager* fm = new FilterManager("fm");
    logger->trace("  Using factory, making 4 general filters...");
	Filter* f1,*f2,*f3,*f4,*f5,*f6,*f7,*f8;
	f1 = FilterFactory::createFilter();
	f2 = FilterFactory::createFilter();
	f3 = FilterFactory::createFilter();
	f4 = FilterFactory::createFilter();
	f5 = FilterFactory::createNullImgFilter();
	f6 = FilterFactory::createNullFPGAFilter();
	f7 = FilterFactory::createFilter();
	f8 = FilterFactory::createFilter();
    logger->trace("  Inserting f1 as \"task 3\" to FRONT...");
	fm->insertFilter("task 3",f1,"FRONT");
    logger->trace("  Inserting f2 as \"task 1\"...");
	fm->insertFilter("task 1",f2,"task 3");
    logger->trace("  Inserting f3 as \"task 2\" between f1,f2...");
	fm->insertFilter("task 2",f3,"task 3");
    logger->trace("  Inserting f4 as \"task 4\" to REAR...");
	fm->insertFilter("task 4",f4);
    logger->trace("  Replacing \"task 3\" with f5 under key \"task 5\"...");
	fm->replaceFilter("task 5",f5,"task 3");
    logger->trace("  Replacing \"FRONT\" with f2 under key \"task 6\"...");
	fm->replaceFilter("task 6",f6,"FRONT");
    logger->trace("  Using getFilterChainIDs()...");
	std::vector<std::string> list = fm->getFilterChainIDs();
	std::string res;
	for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+*it;
    logger->trace("   "+res);
	if (res == " task 6 task 2 task 5 task 4")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, list unexpected");
		fail += 1;
	}
    logger->trace("  Try replacing w/ non unique ID...");
	res = StringTools::intToStr(fm->replaceFilter("task 5",f7,"task 5"));
    logger->trace("    error code: "+res);
	if (res == "2")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, incorrect error");
		fail += 1;
	}
    logger->trace("  Try replacing out of range...");
	res = StringTools::intToStr(fm->replaceFilter("task 8",f8,"what task?"));
    logger->trace("    error code: "+res);
	if (res == "1")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, incorrect error");
		fail += 1;
	}
    logger->trace("  Try replacing using auto ID mode...");
	res = StringTools::intToStr(fm->replaceFilter(f8,"task 2"));
    logger->trace("    error code: "+res);
	if (res == "4")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, incorrect error");
		fail += 1;
	}
	delete fm;
	delete f7;
	delete f8;

    logger->trace(" Test under auto ID mode...");
	fm = new FilterManager("fm",1);
    logger->trace("  Using factory...");
//	Filter* f1,*f2,*f3,*f4,*f5,*f6,*f7,*f8;
	f1 = FilterFactory::createFilter();
	f2 = FilterFactory::createFilter();
	f3 = FilterFactory::createFilter();
	f4 = FilterFactory::createFilter();
	f5 = FilterFactory::createNullImgFilter();
	f6 = FilterFactory::createNullFPGAFilter();
	f7 = FilterFactory::createFilter();
	f8 = FilterFactory::createFilter();
    logger->trace("  Inserting f1 to FRONT...");
	fm->insertFilter(f1,"FRONT");
    logger->trace("  Inserting f2...");
	fm->insertFilter(f2);
    logger->trace("  Inserting f3 between f1,f2...");
	fm->insertFilter(f3,"2 GenericFilter");
    logger->trace("  Inserting f4 to REAR...");
	fm->insertFilter(f4,"REAR");
    logger->trace("  Replacing \"2 GenericFilter\" with f5...");
	fm->replaceFilter(f5,"2 GenericFilter");
    logger->trace("  Replacing \"FRONT\" with f6...");
	fm->replaceFilter(f6,"FRONT");
    logger->trace("  Using getFilterChainIDs()...");
	list = fm->getFilterChainIDs();
	res = "";
	for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+*it;
    logger->trace("   "+res);
	if (res == " 6 NullFPGAFilter 3 GenericFilter 5 NullImgFilter 4 GenericFilter")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, list unexpected");
		fail += 1;
	}
    logger->trace("  Try replacing out of range...");
	res = StringTools::intToStr(fm->insertFilter(f7,"what task?"));
    logger->trace("    error code: "+res);
	if (res == "1")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, incorrect error");
		fail += 1;
	}
	delete fm;
	delete f7;
	delete f8;
    logger->trace("Testing complete.");

	if (fail > 0)
        logger->warn("  TEST FAILED: replaceFilter()");
    logger->trace("==============================");
	return fail;
}
