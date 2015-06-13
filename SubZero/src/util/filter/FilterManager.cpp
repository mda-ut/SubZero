/*
 * FilterManager.cpp
 *
 *  Created on: Feb 19, 2015
 *      Author: ahsueh1996
 */

#include "FilterManager.h"



/* ==========================================================================
 * CONSTRUCTOR AND DESCONSTRUCTOR
 * ==========================================================================
 */

FilterManager::FilterManager(std::string fmID) {
	this->fmID = fmID;
	this->filterCount = 0;
	this->autoID = 0;
	this->fmMode = 0;
	this->filterChain = new IDHasher;
}

FilterManager::FilterManager(std::string fmID, int type) {
	this->fmID = fmID;
	this->filterCount = 0;
	this->autoID = 1;
	this->fmMode = 0;
	this->filterChain = new IDHasher;
	if (type == 1)
		this->fmMode = 1;
}

FilterManager::~FilterManager() {
	this->deleteFilterChain();
	delete(this->filterChain);
}

/* ==========================================================================
 * MAIN FUNCTIONALITY: FILTRATION
 * ==========================================================================
 */

int FilterManager::applyFilterChain(Data* data) {
	int ret = 0, event;
	Node* nxt = this->filterChain->getFront();
	if (data == 0)
		return 2;
	while (nxt != 0)
	{
		event = nxt->nodeData->filter->filter(data);
		if (event != 0)
		{
			data->addMsg("err: " + StringTools::intToStr(event) + " while filtering: " + nxt->nodeData->filter->getID());
			ret = 1;
		}
		nxt = nxt->nxt;
	}
	data->setID(this->fmID);
	return ret;
}

/* ==========================================================================
 * FILTER MANAGMENT FUNCTIONS: CUSTOM ID MODE
 * ==========================================================================
 */

int FilterManager::insertFilter(std::string filterID, Filter* filter) {
	int event;
	std::string targetID = "REAR";
	event = this->insertFilter(filterID,filter,targetID);
	return event;
}

int FilterManager::insertFilter(std::string filterID, Filter* filter, std::string targetID) {
	NodeData* nodeData = new NodeData;
	int event;
	filter->setID(filterID);
	nodeData->filter = filter;
	event = this->filterChain->insByID(filterID,nodeData,targetID);
	return event;
}

int FilterManager::replaceFilter(std::string filterID, Filter* filter, std::string targetID) {
	int event;

	if (targetID == "FRONT")
		targetID = this->filterChain->getFront()->nodeID;
	else if (targetID == "REAR")
		targetID = this->filterChain->getRear()->nodeID;

	event = this->insertFilter(filterID,filter,targetID);
	if (event != 0)
		return event;

	event = this->deleteFilter(targetID);
	return event;
}

int FilterManager::deleteFilter(std::string targetID) {
	int event;

	event = this->filterChain->delByID(targetID);
	return event;
}

void FilterManager::deleteFilterChain() {
	this->filterChain->delAll();
}


/* ==========================================================================
 * FILTER MANAGEMENT: AUTOMATIC ID MODE
 * Auto mode is not recommended since the elements in the filter
 * chain can get to be very ambiguous.
 * ==========================================================================
 */

int FilterManager::insertFilter(Filter* filter) {
	if (this->fmMode != 1)
		return 3;
	else
	{
		std::string generatedID = StringTools::intToStr(this->autoID++) + " " + filter->getID();
		int event = this->insertFilter(generatedID,filter);
		return event;
	}
}

int FilterManager::insertFilter(Filter* filter,std::string targetID) {
	if (this->fmMode != 1)
			return 3;
	else
	{
		std::string generatedID = StringTools::intToStr(this->autoID++) + " " + filter->getID();
		int event = this->insertFilter(generatedID,filter,targetID);
		return event;
	}
}

int FilterManager::replaceFilter(Filter* filter,std::string targetID) {
	if (this->fmMode != 1)
			return 3;
	else
	{
		std::string generatedID = StringTools::intToStr(this->autoID++) + " " + filter->getID();
		int event = this->replaceFilter(generatedID,filter,targetID);
		return event;
	}
}

/* ==========================================================================
 * SUPPLEMENTS
 * ==========================================================================
 */

int FilterManager::getSizeOfFilterChain() {
	 return this->filterChain->getCount();
}

std::vector<std::string> FilterManager::getFilterChainIDs() {
	return this->filterChain->getNodeIDList();
}

std::string FilterManager::getFMID() {
	return this->fmID;
}

int FilterManager::getMode() {
	return this->fmMode;
}

Filter* FilterManager::getFilterByID(std::string targetID) {
	return this->filterChain->get(targetID)->filter;
}
