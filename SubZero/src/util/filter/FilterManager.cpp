/*
 * FilterManager.cpp
 *
 *  Created on: Feb 19, 2015
 *      Author: ahsueh1996
 */

#include "FilterManager.h"

FilterManager::FilterManager(std::string ID) {
	this->ID = ID;
	this->filterCount = 0;
}

FilterManager::~FilterManager() {
	while (!this->deleteFilterChain());
}

int FilterManager::filter(ImgData* in, ImgData** out) {
	int count, event;
	struct Node* nxt = this->filterChain.linkedListFront;
	ImgData* working = DataFactory::createCamData(in);
	while (nxt!=nullptr)
	{
		event = nxt->nodeData->filter->filter(working);
		count++;
		if (event>0)
			return 1;
		nxt = nxt->nxt;
	}
	*out = working;
	return 0;
}

int FilterManager::filter(FPGAData* in, FPGAData** out) {
	int count, event;
	struct Node* nxt = this->filterChain.linkedListFront;
	FPGAData* working = DataFactory::createFPGAData(in);
	while (nxt!=nullptr)
	{
		event = nxt->nodeData->filter->filter(working);
		count++;
		if (event>0)
			return 1;
		nxt = nxt->nxt;
	}
	*out = working;
	return 0;
}

int FilterManager::insertFilter(std::string ID, Filter* filter) {
	struct NodeData data;
	int event;
	data.filter = filter;
	event = this->filterChain.ins(ID,data,-1);
	this->getSizeOfFilter();
	if (event == 1)
		return 1;
	return 0;
}

int FilterManager::insertFilter(std::string ID, Filter* filter, int index) {
	struct NodeData data;
	int event;
	data.filter = filter;
	event = this->filterChain.ins(ID,data,index);
	this->getSizeOfFilter();
	if (event == 1)
		return 1;
	return 0;
}

int FilterManager::replaceFilter(std::string ID, Filter* filter, int index) {
	int event;
	if (index >= this->filterCount or index <= this->filterCount*-1)
		return 2;
	event = this->insertFilter(ID,filter,index);
	if (event == 1)
		return 1;
	event = this->deleteFilterByIndex(index+1);
	if (event == 1)
	{
		this->deleteFilterByIndex(index);
		return 1;
	}
	return 0;
}

int FilterManager::deleteFilterByID(std::string ID) {
	int event;
	event = this->filterChain.del(ID);
	this->getSizeOfFilter();
	if (event == 1)
		return 1;
	return 0;
}

int FilterManager::deleteFilterByIndex(int index) {
	int event;
	event = this->filterChain.del(index);
	this->getSizeOfFilter();
	if (event == 1)
		return 1;
	return 0;
}

int FilterManager::deleteFilterChain() {
	int event;
	event = this->filterChain.delAll();
	this->getSizeOfFilter();
	if (event != 0)
		return 1;
	return 0;
}

int FilterManager::getSizeOfFilter() {
	this->filterCount = this->filterChain.count;
	return this->filterCount;
}

std::vector<std::string> FilterManager::getFilterChainID() {
	return this->filterChain.getList();
}
