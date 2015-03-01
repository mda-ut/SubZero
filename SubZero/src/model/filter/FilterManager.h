/*
 * FilterManager.h
 *
 *  Created on: Feb 19, 2015
 *      Author: ahsueh1996
 */

#ifndef FILTERMANAGER_H_
#define FILTERMANAGER_H_

#include "Filter.h"
#include <vector>

class FilterManager {
public:
	FilterManager();
	virtual ~FilterManager();

	// The filter() function accepts a raw data input. Depending on
	// what kind of model it belongs to it takes in a image or FPGA
	// data and returns the corresponding type.
	// Raw data is passed as a pointer and the function will make
	// changes to the data (not the copy of the data).
	void filter(CamData * raw);
	// This is the overloaded filter function for filtering FPGA input.
	void filter(FPGAData * raw);

	// Inserts a Filter class object to the back of the chain.
	void insertFilter(Filter * filter);

	// Inserts a Filter class object to a certain index and right shifting
	// the rest of the filters in the chain.
	void insertFilter(Filter * filter, int index);

	// Replaces a particular filter in the chain with another, by index.
	// if index is out of range, function will default to insert to back.
	void replaceFilter(Filter * filter, int index);

	// Deletes the first occurrence of a filter from filterChain by ID.
	void deleteFilterByID(std::string ID);

	// Deletes all occurrences of a filter from chain by ID with overload 1.
	// Overload is 0 by default and removes first occurrence.
	void deleteFilterByID(std::string ID, int type);

	// Deletes the first occurrence of a filter from filterChain by index.
	void deleteFilterByIndex(int index);

	// Deletes filters by index in same overloading patterns as previous func.
	void deleteFilterByIndex(int index, int type);

	// Reports the size of filterChian vector.
	int getSizeOfFilter();

	// Reports a copy of the vector string of filter IDs in filterChain.
	std::vector getFilterChain();

	// Reports the index of the first occurrence of a particular filter ID.
	int getFilterIndexByID(std::string ID);

	// Reports the index of all occurrences of a particular filter ID.
	std::vector getFilterIndexByID(std::string ID, int type);

private:

	// The main item FilterManager will manage is the filterChain,
	// a data structure that contains all the filters to be applied
	// to some image or data.
	std::vector<Filter> filterChain;

	// In direct correspondence to filterChain, filterChainID holds
	// string identifiers for each of the filters created.
	std::vector<std::string> filterChainID;

};

#endif /* FILTERMANAGER_H_ */
