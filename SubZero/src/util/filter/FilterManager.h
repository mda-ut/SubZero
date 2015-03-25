/*
 * FilterManager.h
 *
 *  Created on: Feb 19, 2015
 *      Author: ahsueh1996
 */

#ifndef FILTERMANAGER_H_
#define FILTERMANAGER_H_

#include "Filter.h"
#include "IDHasher.h"
#include "DataFactory.h"
#include <vector>

struct Data {
	Filter* filter;
};

class FilterManager {

public:
	FilterManager(std::string ID);
	/*
	 * FilterManager constructor initializes a new FilterManager object for
	 * use.
	 *
	 * @param Identifier of the FilterManager, data processed by this FM will have this ID. (ID is recommended to reflect FM's function and is unique! Uniqueness is a feature only for when the FMs are processing data to store in state, thus FM won't enforce ID uniqueness.)
	 */

	virtual ~FilterManager();

	/*
	 * The filter() function accepts a raw data input. Depending on
	 * what kind of model it belongs to, it takes in a image or FPGA
	 * data and filters it according to the current filter chain.
	 *
	 * @param in refers to a pointer to the image being filtered.
	 * @param out refers to the pointer that will receive the filtered data.
	 * @return int 0 for success, 1 for there is some error in filtering.
	 */
	int filter(ImgData* in, ImgData* &out);

	/*
	 * This is the overloaded filter function for filtering FPGA input.
	 *
	 * @see filter overloaded with CamData types.
	 */
	int filter(FPGAData* in, FPGAData* &out);


	/*
	int filter(genData* in, genData* out) {
		ImgData* temp = (ImgData*) in;
		out = (genData*) temp;
	}*/


	/*
	 * Inserts a Filter class object to the back of the chain. Note: ID is
	 * required here to maintain uniqueness of IDs.
	 *
	 * @param ID is the unique identifier chosen by the owner of the filter.
	 * @param filter, a pointer to a filter object.
	 * @return 0 for success, 1 for ID is not unique.
	 */
	int insertFilter(std::string ID, Filter* filter);

	/*
	 * Inserts a Filter class object at certain index and right shifting
	 * the rest of the filters in the chain.
	 *
	 * @param ID is the unique identifier chosen by the owner of the filter.
	 * @param filter, a pointer to a filter object.
	 * @param index, the location to insert the filter.
	 * @return 0 for success, 1 for ID is not unique.
	 */
	int insertFilter(std::string ID, Filter* filter, int index);

	/*
	 * Replaces a particular filter in the chain with another, by index.
	 * if index is out of range, function will NOT perform insertion and
	 * return the appropriate error code.
	 *
	 * @param ID is the unique identifier chosen by the owner of the filter.
	 * @param filter, a pointer to a filter object.
	 * @param index, the location to insert the filter.
	 * @return 0 for success, 1 for ID not unique, 2 for index out of range.
	 */
	int replaceFilter(std::string ID, Filter* filter, int index);

	/*
	 * Deletes the first occurrence of a filter from filterChain by ID.
	 *
	 * @param ID
	 * @return 0 for success, 1 for ID not found.
	 */
	int deleteFilterByID(std::string ID);

	/*
	 * Deletes the first occurrence of a filter from filterChain by index.
	 *
	 * @param index
	 * @return 0 for success, 1 for index out of range.
	 */
	int deleteFilterByIndex(int index);

	/*
	 * Deletes all filters in chain.
	 *
	 * @return 0 for success.
	 */
	int deleteFilterChain();

	/*
	 * Reports the number of filters in filterChain.
	 *
	 * @return number of filters.
	 */
	int getSizeOfFilter();

	/*
	 * Reports a copy of the vector string of filter IDs in filterChain.
	 *
	 * @return vector of strings
	 */
	std::vector<std::string> getFilterChainID();

private:
	/*
	 * The main item FilterManager will manage is the filterChain,
	 * a data structure that contains all the filters to be applied
	 * to some image or data.
	 */
	IDHasher filterChain;

	// Count of how many filters
	int filterCount;

	// Identifier for the FM
	std::string ID;
};

#endif /* FILTERMANAGER_H_ */
