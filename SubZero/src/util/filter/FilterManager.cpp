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
    filterCount = 0;
    autoID = 0;
    fmMode = 0;
    filterChain = new IDHasher();
}

FilterManager::FilterManager(std::string fmID, int type) {
    this->fmID = fmID;
    filterCount = 0;
    autoID = 1;
    fmMode = type;
    filterChain = new IDHasher();
}

FilterManager::~FilterManager() {
    delete filterChain;
    delete logger;
}

/* ==========================================================================
 * MAIN FUNCTIONALITY: FILTRATION
 * ==========================================================================
 */

int FilterManager::applyFilterChain(Data* data) {
    int ret = 0;
    int event = 0;
    Node* nxt = filterChain->getFront();
    if (data == 0) {
        logger->debug("Cannot filter null data");
        return 2;
    }
    while (nxt != 0) {
        event = nxt->nodeData->filter->filter(data);
        if (event != 0) {
            logger->error("Error while filtering using filter " + nxt->nodeData->filter->getID());
            data->addMsg("err: " + StringTools::intToStr(event) + " while filtering: " + nxt->nodeData->filter->getID());
            ret = 1;
        }
        nxt = nxt->nxt;
    }
    data->setID(fmID);
    return ret;
}

/* ==========================================================================
 * FILTER MANAGMENT FUNCTIONS: CUSTOM ID MODE
 * ==========================================================================
 */

int FilterManager::insertFilter(std::string filterID, Filter* filter) {
    int event;
    std::string targetID = "REAR";
    event = insertFilter(filterID, filter, targetID);
    return event;
}

int FilterManager::insertFilter(std::string filterID, Filter* filter, std::string targetID) {
    if (filter == 0) {
        logger->debug("Cannot insert null filter");
        return 3;
    }
    NodeData* nodeData = new NodeData();
    filter->setID(filterID);
    nodeData->filter = filter;
    int event = filterChain->insByID(filterID, nodeData, targetID);
    if (event != 0) {
        nodeData->filter = 0;
        delete nodeData;
    }
    return event;
}

int FilterManager::replaceFilter(std::string filterID, Filter* filter, std::string targetID) {
    int event = 0;

    if (targetID == "FRONT") {
        targetID = filterChain->getFront()->nodeID;
    }
    else if (targetID == "REAR") {
        targetID = filterChain->getRear()->nodeID;
    }

    event = insertFilter(filterID, filter, targetID);
    if (event != 0) {
        return event;
    }

    event = deleteFilter(targetID);
    return event;
}

int FilterManager::deleteFilter(std::string targetID) {
    int event = filterChain->delByID(targetID);
    return event;
}

void FilterManager::deleteFilterChain() {
    filterChain->delAll();
}


/* ==========================================================================
 * FILTER MANAGEMENT: AUTOMATIC ID MODE
 * Auto mode is not recommended since the elements in the filter
 * chain can get to be very ambiguous.
 * ==========================================================================
 */

int FilterManager::insertFilter(Filter* filter) {
    if (fmMode != 1) {
        return 4;
    } else {
        std::string generatedID = StringTools::intToStr(autoID++) + " " + filter->getID();
        int event = insertFilter(generatedID,filter);
        return event;
    }
}

int FilterManager::insertFilter(Filter* filter, std::string targetID) {
    if (fmMode != 1) {
        return 4;
    } else {
        std::string generatedID = StringTools::intToStr(autoID++) + " " + filter->getID();
        int event = insertFilter(generatedID, filter, targetID);
        return event;
    }
}

int FilterManager::replaceFilter(Filter* filter,std::string targetID) {
    if (fmMode != 1) {
        return 4;
    } else {
        std::string generatedID = StringTools::intToStr(autoID++) + " " + filter->getID();
        int event = replaceFilter(generatedID,filter,targetID);
        return event;
    }
}

/* ==========================================================================
 * SUPPLEMENTS
 * ==========================================================================
 */

int FilterManager::getSizeOfFilterChain() {
     return filterChain->getCount();
}

std::vector<std::string> FilterManager::getFilterChainIDs() {
    return filterChain->getNodeIDList();
}

std::string FilterManager::getFMID() {
    return fmID;
}

int FilterManager::getMode() {
    return fmMode;
}

Filter* FilterManager::getFilterByID(std::string targetID) {
    return filterChain->get(targetID)->filter;
}
