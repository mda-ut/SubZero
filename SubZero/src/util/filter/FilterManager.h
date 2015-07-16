/*
 * FilterManager.h
 *
 *  Created on: Feb 19, 2015
 *      Author: ahsueh1996
 */

#ifndef FILTERMANAGER_H_
#define FILTERMANAGER_H_

#include "Filter.h"
#include "../IDHasher.h"
#include "../data/Data.h"
#include "../data/DataFactory.h"
#include "../StringTools.h"
#include <vector>

/**
 * The main job of a FilterManager, identified by its FMID, is to use
 * a ordered set of user defined filters to filter data. Reference
 * data is passed to the FM and a filtered deep copy of that data is
 * then referenced back out to the user. FM tags each filtered data
 * with its FMID to signify its responsibility for the data point. FM
 * also manages the ordered set of filters and provide basic functions:
 * insert, replace and delete for the user to easily alter the set of
 * filters hereby referred to as the filterChain. To manage the
 * filterChain, users are given to opportunity to give each filter a
 * customized ID and be able to access the filters in a personalized
 * manner. Should the user feel not want the need of custom IDing, the
 * automatic IDing mode will complete the process with stock IDs that
 * the user can then use to refer to the filters.
 */
class FilterManager {

private:
    /* ==========================================================================
     * CLASS VARIABLES
     * ==========================================================================
     */

    Logger* logger = new Logger("FilterManager");

    /*
     * The main item FilterManager will manage is the filterChain,
     * a data structure that contains all the filters to be applied
     * to some image or data.
     */
    IDHasher* filterChain;

    /*
     * Count of how many filters
     */
    int filterCount;

    /*
     * Enumeration of a unique integer used when FM is in automatic
     * ID mode.
     */
    int autoID;

    /*
     * Identifier for the FM
     */
    std::string fmID;

    /*
     * FilterManager mode, 0 for default, 1 for auto.
     */
    int fmMode;

public:
    /* ==========================================================================
     * CONSTRUCTOR AND DESCONSTRUCTOR
     * ==========================================================================
     */

    /**
     * FilterManager constructor initializes a new FilterManager object for
     * use. The data processed by this FM will be tagged with the FM's ID.
     *
     * @param fmID	Identifier of the FilterManager, data processed by this FM will have this ID. (ID is recommended to reflect FM's function and is unique! Uniqueness is a feature only for when the FMs are processing data to store in state, thus FM won't enforce ID uniqueness.)
     */
    FilterManager(std::string fmID);

    /**
     * FilterManager constructor overload allows user to initiate a FM that
     * will do automatic IDing of the filters it manages. In comparison, the
     * default class allows customized IDing.
     *
     * @param fmID	Identifier of the FilterManager, data processed by this FM will have this ID. (ID is recommended to reflect FM's function and is unique! Uniqueness is a feature only for when the FMs are processing data to store in state, thus FM won't enforce ID uniqueness.)
     * @param 		1 for automatic IDing. 0 for default.
     */
    FilterManager(std::string fmID, int type);

    virtual ~FilterManager();

    /* ==========================================================================
     * MAIN FUNCTIONALITY: FILTRATION
     * ==========================================================================
     */

    /**
     * This function accepts a raw data input. Depending on
     * what kind of model it belongs to, it takes in a image or FPGA
     * data and filters it according to the current filter chain.
     *
     * @param input 	refers to a pointer to the image to be filtered.
     * @return 			0 for success, 1 for there is some error in filtering, 2 for null pointer.
     */
    int applyFilterChain(Data* data);


    /* ==========================================================================
     * FILTER MANAGMENT FUNCTIONS: CUSTOM ID MODE
     * ==========================================================================
     */

    /**
     * Inserts a Filter class object to the back of the chain. Note: ID
     * initialization is required here rather than at the filter object
     * level because 1. filters don't need an ID to function and 2. If
     * ID is given to FM, it helps FM to maintain uniqueness of IDs.
     *
     * @param ID 		is the unique identifier chosen by the owner of the filter.
     * @param filter	the pointer to a filter object.
     * @return 			0 for success, 2 for ID is not unique, 3 for null filter.
     */
    int insertFilter(std::string filterID, Filter* filter);

    /**
     * Inserts a Filter class object in front of a specific target
     * filter (by ID).
     *
     * @param ID 		of the new filter.
     * @param filter 	the a pointer to a filter object to be inserted.
     * @param targetID 	the location to perform insertion. BEGIN and END keywords are also recognized.
     * @return 			0 for success, 1 for target not found, 2 for ID is not unique, 3 for null filter.
     */
    int insertFilter(std::string filterID, Filter* filter, std::string targetID);

    /**
     * Replaces a particular filter, identified by ID, in the chain with
     * another. If ID not found, function will NOT perform insertion and
     * will instead return the appropriate error code.
     *
     * @param ID 		of the new filter.
     * @param filter 	the pointer to a filter object that will be inserted.
     * @param targetID	the old filter to replace.
     * @return 			0 for success, 1 for targetID not found, 2 for ID not unique, 3 for null filter.
     */
    int replaceFilter(std::string filterID, Filter* filter, std::string targetID);

    /**
     * Deletes the first occurrence of a filter from filterChain by ID.
     *
     * @param targetID 	of the filter to delete. BEGIN and END keywords accepted.
     * @return 			0 for success, 1 for targetID not found.
     */
    int deleteFilter(std::string targetID);

    /**
     * Deletes all filters in filterChain.
     */
    void deleteFilterChain();

    /* ==========================================================================
     * FILTER MANAGEMENT: AUTOMATIC ID MODE
     * Auto mode is not recommended since the elements in the filter
     * chain can get to be very ambiguous.
     * ==========================================================================
     */

    /**
     * Insertion to back under automatic IDing mode.
     *
     * @param filter 	is a pointer to a filter object.
     * @return 			0 for success, , 3 for null filter, 4 for not in auto mode.
     */
    int insertFilter(Filter* filter);

    /**
     * Inserts a Filter class object in front of a specific target
     * filter (by ID). This is the overload function under automatic ID
     * mode.
     *
     * @param filter 	is a pointer to a filter object to be inserted.
     * @param targetID	is the location to perform insertion. FRONT and BACK keywords are also recognized.
     * @return 			0 for success, 1 for target not found, 3 for null filter, 4 for not in auto mode.
     */
    int insertFilter(Filter* filter, std::string targetID);

    /**
     * Replacement under automatic IDing mode.
     * If targetID not found, function will NOT perform insertion and
     * will instead return the appropriate error code.
     *
     * @param filter	is a pointer to a filter object that will be inserted.
     * @param targetID  is the old filter to replace.
     * @return 			0 for success, 1 for targetID not found, 3 for null filter, 4 for not in auto mode.
     */
    int replaceFilter(Filter* filter, std::string targetID);

    /* ==========================================================================
     * SUPPLEMENTS
     * ==========================================================================
     */

    /**
     * Reports the number of filters in filterChain.
     *
     * @return number of filters in filterChain.
     */
    int getSizeOfFilterChain();

    /**
     * Reports a copy of the vector string of filter IDs in filterChain.
     *
     * @return vector of strings
     */
    std::vector<std::string> getFilterChainIDs();

    /**
     * Report the ID of the FM.
     *
     * @return string fmID
     */
    std::string getFMID();

    /**
     * Report the operating mode of the FM.
     *
     * @return int mode, 0 for normal, 1 for auto.
     */
    int getMode();

    /**
     * Return the filter by ID.
     *
     * @param targetID	ID of the filter to return
     * @return			the filter itself
     */
    Filter* getFilterByID(std::string targetID);
};

#endif /* FILTERMANAGER_H_ */
