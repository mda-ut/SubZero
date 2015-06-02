/*
 * FilterManagerTEST.cpp
 *
 *  Created on: May 19, 2015
 *      Author: ahsueh1996
 */

#include "FilterManagerTEST.h"

/* TEMPLATE
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	if (fail > 0)
		Logger::warn("  TEST FAILED: _______");
	Logger::trace("==============================");
	Logger::close();
	return fail;
 */

int FilterManagerTEST::runUnits() {
    int res = 0;
	Logger::trace("Running all unit tests for: FilterManager");
	Logger::trace("==============================");
	res += T_Constructor();
	res += T_applyFilterChain();
	res += T_insertFilter();
	res += T_replaceFilter();
	Logger::trace("==============================");
	if (res != 0)
		Logger::warn(StringTools::intToStr(res)+" warning(s) in unit tests");
	Logger::trace("Unit testing complete: FilterManager");
	return res;
}

/* ==========================================================================
 * CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */

int FilterManagerTEST::T_Constructor() {
	int fail = 0;

	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	Logger::trace("Testing FilterManager constructor:");
	Logger::trace(" Constructing normal mode fm under ID \"normal fm\"...");
	FilterManager* fm = new FilterManager("normal fm");
	Logger::trace("  Complete.");
	Logger::trace(" Accessing initialized parameters...");
	Logger::trace("  Using getFMID()...");
	Logger::trace("    "+fm->getFMID());
	if (fm->getFMID() == "normal fm")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, fmID incorrect");
		fail++;
	}
	Logger::trace("  Using getCount()...");
	Logger::trace("    "+StringTools::intToStr(fm->getSizeOfFilterChain()));
	if (fm->getSizeOfFilterChain() == 0)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, size of filter chain not 0");
		fail++;
	}
	Logger::trace("  Using getMode()...");
	if (fm->getMode() == 0)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok: Mode incorrect");
		fail += 1;
	}
	Logger::trace("  Complete.");
	Logger::trace(" Deleting \"normal fm\"...");
	delete fm;
	Logger::trace(" Constructing normal mode fm under ID \"auto fm\"...");
	fm = new FilterManager("auto fm",1);
	Logger::trace("  Complete.");
	Logger::trace(" Accessing initialized parameters...");
	Logger::trace("  Using getFMID()...");
	Logger::trace("    "+fm->getFMID());
	if (fm->getFMID() == "auto fm")
			Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, fmID incorrect");
		fail++;
	}
	Logger::trace("  Using getCount()...");
	Logger::trace("    "+StringTools::intToStr(fm->getSizeOfFilterChain()));
	if (fm->getSizeOfFilterChain() == 0)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, size of filter chain not 0");
		fail++;
	}
	Logger::trace("  Using getMode()...");
	if (fm->getMode() == 1)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok: Mode incorrect");
		fail += 1;
	}
	Logger::trace("  Complete.");
	delete fm;
	Logger::trace("Testing complete.");

	if (fail > 0)
		Logger::warn("  TEST FAILED: FilterManager constructor");
	Logger::trace("==============================");
	Logger::close();
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
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	Logger::trace("Testing applyFilterChain():");
	Logger::trace(" Creating FM under normal mode...");
	FilterManager* fm = new FilterManager("fm");
	Logger::trace(" Using factory, making 4 random filters...");
	Filter* f1,*f2,*f3,*f4;
	f1 = FilterFactory::createFilter();
	f2 = FilterFactory::createNullImgFilter();
	f3 = FilterFactory::createNullFPGAFilter();
	f4 = FilterFactory::createFilter();
	Logger::trace(" Inserting f1 as \"task 3\" to FRONT...");
	fm->insertFilter("task 3",f1,"FRONT");
	Logger::trace(" Inserting f2 as \"task 1\"...");
	fm->insertFilter("task 1",f2,"task 3");
	Logger::trace(" Inserting f3 as \"task 2\" between f1,f2...");
	fm->insertFilter("task 2",f3,"task 3");
	Logger::trace(" Inserting f4 as \"task 4\" to REAR...");
	fm->insertFilter("task 4",f4);
	Logger::trace(" Making img objs...");
	cv::Mat img ;//= cv::Mat::eye(2,2,CV_32S);
	ImgData* data = new ImgData("input",&img);
	Logger::trace(" Applying all filters...");
	int res = fm->applyFilterChain(data);
	Logger::trace("    "+data->getTrack()+"error code "+StringTools::intToStr(res));
	if (data->getTrack() == "task 1; task 2-1; task 3; task 4; ")
		if (res == 1)
			Logger::trace("    ok");
		else {
			Logger::warn("    NOT ok, error code incorrect");
		}
	else {
		Logger::warn("    NOT ok, track record not expected");
	}
	Logger::trace("Testing complete.");

	if (fail > 0)
		Logger::warn("  TEST FAILED: applyFilterChain");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

/* ==========================================================================
 * FILTER MANAGMENT FUNCTIONS: CUSTOM ID MODE and AUTO ID MODE
 * ==========================================================================
 */

int FilterManagerTEST::T_insertFilter() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	Logger::trace("Testing insertFilter():");
	Logger::trace(" Test under custom ID mode...");
	FilterManager* fm = new FilterManager("fm");
	Logger::trace("  Using factory, making 4 general filters...");
	Filter* f1,*f2,*f3,*f4;
	f1 = FilterFactory::createFilter();
	f2 = FilterFactory::createFilter();
	f3 = FilterFactory::createFilter();
	f4 = FilterFactory::createFilter();
	Logger::trace("  Inserting f1 as \"task 3\" to FRONT...");
	fm->insertFilter("task 3",f1,"FRONT");
	Logger::trace("  Inserting f2 as \"task 1\"...");
	fm->insertFilter("task 1",f2,"task 3");
	Logger::trace("  Inserting f3 as \"task 2\" between f1,f2...");
	fm->insertFilter("task 2",f3,"task 3");
	Logger::trace("  Inserting f4 as \"task 4\" to REAR...");
	fm->insertFilter("task 4",f4);
	Logger::trace("  Using getFilterChainIDs()...");
	std::vector<std::string> list = fm->getFilterChainIDs();
	std::string res;
	for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+*it;
	Logger::trace("   "+res);
	if (res == " task 1 task 2 task 3 task 4")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, list unexpected");
		fail += 1;
	}
	Logger::trace("  Try inserting w/ non unique ID...");
	res = StringTools::intToStr(fm->insertFilter("task 2",f2));
	Logger::trace("    error code: "+res);
	if (res == "2")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, incorrect error");
		fail += 1;
	}
	Logger::trace("  Try inserting out of range...");
	res = StringTools::intToStr(fm->insertFilter("task 2",f2,"what task?"));
	Logger::trace("    error code: "+res);
	if (res == "1")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, incorrect error");
		fail += 1;
	}
	Logger::trace("  Try inserting with no filterID arg...");
	res = StringTools::intToStr(fm->insertFilter(f2,"Task 2"));
	Logger::trace("    error code: "+res);
	if (res == "3")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, incorrect error");
		fail += 1;
	}
	delete fm;

	Logger::trace(" Test under auto ID mode...");
	fm = new FilterManager("fm",1);
	Logger::trace("  Using factory, making 4 general filters...");
	f1 = FilterFactory::createFilter();
	f2 = FilterFactory::createFilter();
	f3 = FilterFactory::createFilter();
	f4 = FilterFactory::createFilter();
	Logger::trace("  Inserting f1 to FRONT...");
	fm->insertFilter(f1,"FRONT");
	Logger::trace("  Inserting f2...");
	fm->insertFilter(f2);
	Logger::trace("  Inserting f3 between f1,f2...");
	fm->insertFilter(f3,"2 GenericFilter");
	Logger::trace("  Inserting f4 to REAR...");
	fm->insertFilter(f4,"REAR");
	res = "";
	Logger::trace("  Using getFilterChainIDs()...");
	list = fm->getFilterChainIDs();
	for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+*it;
	Logger::trace("   "+res);
	if (res == " 1 GenericFilter 3 GenericFilter 2 GenericFilter 4 GenericFilter")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, list unexpected");
		fail += 1;
	}
	Logger::trace("  Try inserting w/ custom ID...");
	res = StringTools::intToStr(fm->insertFilter("task 2",f2));
	Logger::trace("    error code: "+res);
	if (res == "0")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, incorrect error");
		fail += 1;
	}
	Logger::trace("  Try inserting out of range...");
	res = StringTools::intToStr(fm->insertFilter(f2,"what task?"));
	Logger::trace("    error code: "+res);
	if (res == "1")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, incorrect error");
		fail += 1;
	}
	Logger::trace("Testing complete.");
//	delete fm;

	if (fail > 0)
		Logger::warn("  TEST FAILED: insertFilter()");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

int FilterManagerTEST::T_replaceFilter() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	Logger::trace("Testing replaceFilter():");
	Logger::trace(" Test under custom ID mode...");
	FilterManager* fm = new FilterManager("fm");
	Logger::trace("  Using factory, making 4 general filters...");
	Filter* f1,*f2,*f3,*f4,*f5,*f6,*f7,*f8;
	f1 = FilterFactory::createFilter();
	f2 = FilterFactory::createFilter();
	f3 = FilterFactory::createFilter();
	f4 = FilterFactory::createFilter();
	f5 = FilterFactory::createNullImgFilter();
	f6 = FilterFactory::createNullFPGAFilter();
	f7 = FilterFactory::createFilter();
	f8 = FilterFactory::createFilter();
	Logger::trace("  Inserting f1 as \"task 3\" to FRONT...");
	fm->insertFilter("task 3",f1,"FRONT");
	Logger::trace("  Inserting f2 as \"task 1\"...");
	fm->insertFilter("task 1",f2,"task 3");
	Logger::trace("  Inserting f3 as \"task 2\" between f1,f2...");
	fm->insertFilter("task 2",f3,"task 3");
	Logger::trace("  Inserting f4 as \"task 4\" to REAR...");
	fm->insertFilter("task 4",f4);
	Logger::trace("  Replacing \"task 3\" with f5 under key \"task 5\"...");
	fm->replaceFilter("task 5",f5,"task 3");
	Logger::trace("  Replacing \"FRONT\" with f2 under key \"task 6\"...");
	fm->replaceFilter("task 6",f6,"FRONT");
	Logger::trace("  Using getFilterChainIDs()...");
	std::vector<std::string> list = fm->getFilterChainIDs();
	std::string res;
	for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+*it;
	Logger::trace("   "+res);
	if (res == " task 6 task 2 task 5 task 4")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, list unexpected");
		fail += 1;
	}
	Logger::trace("  Try replacing w/ non unique ID...");
	res = StringTools::intToStr(fm->replaceFilter("task 5",f7,"task 5"));
	Logger::trace("    error code: "+res);
	if (res == "2")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, incorrect error");
		fail += 1;
	}
	Logger::trace("  Try replacing out of range...");
	res = StringTools::intToStr(fm->replaceFilter("task 8",f8,"what task?"));
	Logger::trace("    error code: "+res);
	if (res == "1")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, incorrect error");
		fail += 1;
	}
	Logger::trace("  Try replacing using auto ID mode...");
	res = StringTools::intToStr(fm->replaceFilter(f8,"task 2"));
	Logger::trace("    error code: "+res);
	if (res == "3")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, incorrect error");
		fail += 1;
	}
	delete fm;
	delete f7;
	delete f8;

	Logger::trace(" Test under auto ID mode...");
	fm = new FilterManager("fm",1);
	Logger::trace("  Using factory...");
//	Filter* f1,*f2,*f3,*f4,*f5,*f6,*f7,*f8;
	f1 = FilterFactory::createFilter();
	f2 = FilterFactory::createFilter();
	f3 = FilterFactory::createFilter();
	f4 = FilterFactory::createFilter();
	f5 = FilterFactory::createNullImgFilter();
	f6 = FilterFactory::createNullFPGAFilter();
	f7 = FilterFactory::createFilter();
	f8 = FilterFactory::createFilter();
	Logger::trace("  Inserting f1 to FRONT...");
	fm->insertFilter(f1,"FRONT");
	Logger::trace("  Inserting f2...");
	fm->insertFilter(f2);
	Logger::trace("  Inserting f3 between f1,f2...");
	fm->insertFilter(f3,"2 GenericFilter");
	Logger::trace("  Inserting f4 to REAR...");
	fm->insertFilter(f4,"REAR");
	Logger::trace("  Replacing \"2 GenericFilter\" with f5...");
	fm->replaceFilter(f5,"2 GenericFilter");
	Logger::trace("  Replacing \"FRONT\" with f6...");
	fm->replaceFilter(f6,"FRONT");
	Logger::trace("  Using getFilterChainIDs()...");
	list = fm->getFilterChainIDs();
	res = "";
	for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+*it;
	Logger::trace("   "+res);
	if (res == " 6 NullFPGAFilter 3 GenericFilter 5 NullImgFilter 4 GenericFilter")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, list unexpected");
		fail += 1;
	}
	Logger::trace("  Try replacing out of range...");
	res = StringTools::intToStr(fm->insertFilter(f7,"what task?"));
	Logger::trace("    error code: "+res);
	if (res == "1")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, incorrect error");
		fail += 1;
	}
	delete fm;
	delete f7;
	delete f8;
	Logger::trace("Testing complete.");

	if (fail > 0)
		Logger::warn("  TEST FAILED: replaceFilter()");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}
