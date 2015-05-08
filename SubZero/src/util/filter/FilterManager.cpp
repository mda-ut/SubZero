/*
 * FilterManager.cpp
 *
 *  Created on: Feb 19, 2015
 *      Author: ahsueh1996
 */

#include "FilterManager.h"
//
//
//
///* ==========================================================================
// * CONSTRUCTOR AND DESCONSTRUCTOR
// * ==========================================================================
// */
//
//FilterManager::FilterManager(std::string fmID) {
//	this->fmID = fmID;
//	this->filterCount = 0;
//	this->autoID = 0;
//	this->fmMode = 0;
//	this->filterChain = new IDHasher;
//}
//
//FilterManager::FilterManager(std::string fmID, int type) {
//	this->fmID = fmID;
//	this->filterCount = 0;
//	this->autoID = 0;
//	this->fmMode = 0;
//	this->filterChain = new IDHasher;
//	if (type == 1)
//		this->fmMode = 1;
//}
//
//FilterManager::~FilterManager() {
//	int count = 0;
//	this->deleteFilterChain();
//	delete(this->filterChain);
//}
//
///* ==========================================================================
// * MAIN FUNCTIONALITY: FILTRATION
// * ==========================================================================
// */
//
//int FilterManager::applyFilterChain(Data* input, Data** output) {
//	int count, event;
//	struct Node* nxt = this->filterChain.linkedListFront;
//	Data* working = input;
//	if (working == nullptr)
//		return 2;
//	while (nxt != nullptr)
//	{
//		event = nxt->nodeData->filter->filter(working);
//		count++;
//		if (event>0)
//		{
//			working->msg = "err: " + std::to_string(event) + " while filtering: " + nxt->nodeData->filter->getID();
//			return 1;
//		}
//		nxt = nxt->nxt;
//	}
//	*output = working;
//	return 0;
//}
//
///* ==========================================================================
// * FILTER MANAGMENT FUNCTIONS: CUSTOM ID MODE
// * ==========================================================================
// */
//
//int FilterManager::insertFilter(std::string filterID, Filter* filter) {
//	int event;
//	std::string targetID = this->filterChain.linkedListRear->nodeData->filter->filterID;
//	event = this->insertFilter(filterID,filter,targetID);
//	return event;
//}
//
//int FilterManager::insertFilter(std::string filterID, Filter* filter, std::string targetID) {
//	struct NodeData data;
//	int event;
//	data.filter = filter;
//	event = this->filterChain.ins(filterID,data,targetID);
//	if (event != 0)
//		return 1;
//	return 0;
//}
//
//int FilterManager::replaceFilter(std::string filterID, Filter* filter, std::string targetID) {
//	int event;
//
//	event = this->insertFilter(filterID,filter,targetID);
//	if (event != 0)
//		return 1;
//
//	event = this->deleteFilter(targetID);
//	if (event != 0)
//		return 2;
//
//	return 0;
//}
//
//int FilterManager::deleteFilter(std::string targetID) {
//	int event;
//
//	event = this->filterChain.del(targetID);
//	if (event != 0)
//		return 1;
//	return 0;
//}
//
//void FilterManager::deleteFilterChain() {
//	this->filterChain.delAll();
//}
//
//
///* ==========================================================================
// * FILTER MANAGEMENT: AUTOMATIC ID MODE
// * Auto mode is not recommended since the elements in the filter
// * chain can get to be very ambiguous.
// * ==========================================================================
// */
//
//int FilterManager::insertFilter(Filter* filter) {
//	if (this->fmMode != 1)
//		return 1;
//	else
//	{
//		std::string generatedID = this->autoID++ + filter->getID();
//		int event = this->insertFilter(generatedID,filter);
//		return event;
//	}
//}
//
//int FilterManager::insertFilter(Filter* filter,std::string targetID) {
//	if (this->fmMode != 1)
//			return 1;
//	else
//	{
//		std::string generatedID = this->autoID++ + filter->getID();
//		int event = this->insertFilter(generatedID,filter,targetID);
//		return event;
//	}
//}
//
//int FilterManager::replaceFilter(Filter* filter,std::string targetID) {
//	if (this->fmMode != 1)
//			return 1;
//	else
//	{
//		std::string generatedID = this->autoID++ + filter->getID();
//		int event = this->replaceFilter(generatedID,filter,targetID);
//		return event;
//	}
//}
//
///* ==========================================================================
// * SUPPLEMENTS
// * ==========================================================================
// */
//
//int FilterManager::getSizeOfFilterChain() {
//	 return this->filterChain.getCount();
//}
//
//std::vector<std::string> FilterManager::getFilterChainIDs() {
//	return this->filterChain.getList();
//}
//
//std::string FilterManager::getFMID() {
//	return this->fmID;
//}
