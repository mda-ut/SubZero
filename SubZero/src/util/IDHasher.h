/*
 * IDHasher.h
 *
 *  Created on: Mar 14, 2015
 *      Author: ahsueh1996
 */

#ifndef IDHASHER_H_
#define IDHASHER_H_
#include <map>
#include <vector>
#include <string>


/*
 * Nodes of the linked list
 */

struct Node {
	struct Node* nxt;
	struct Node* prv;
	struct NodeData* nodeData;
	std::string nodeID;
};

/*
 * The IDHasher is an ADT using a combination of map and linked
 * list to allow user to store and access data via mapping from
 * a string key (custom user set ID) to the data. Data struct is
 * left to the user of the ADT to define and is contained in
 * nodes. Nodes are linked to each other to retain a sequential
 * ordering (which is otherwise lost in a regular map object).
 */
class IDHasher {

private:
	/* ==========================================================================
	 * CLASS VARIABLES
	 * ==========================================================================
	 */

	/*
	 * Dictionary to map ID to nodes in the linked list
	 */
	std::map<std::string, struct Node*> dictionary;


public:

	/* ==========================================================================
	 * PUBLIC CLASS VARIABLES
	 * ==========================================================================
	 */

	/*
	 * Linked List pointers
	 */
	struct Node* linkedListFront;
	struct Node* linkedListRear;


	/*
	 * Count of nodes/data stored by ADT
	 */
	int count;

	/* ==========================================================================
	 * CONSTRUCTOR AND DESTRUCTOR
	 * ==========================================================================
	 */

	/**
	 * Constructor stub.
	 */
	IDHasher ();

	/**
	 * Destructor stub.
	 */
	virtual ~IDHasher ();

	/* ==========================================================================
	 * BASIC ADT METHODS
	 * ==========================================================================
	 */

	/**
	 * Search and returns a ptr to the data. It should be noted
	 * that the Data struct is a wrapper for the real data being
	 * requested. User of IDHasher could use their definition of
	 * struct Data to return the desired data.
	 *
	 * @param ID 			is the string key associated to a stored data.
	 * @return nodeData*	which is a wrapper class for the "real data."
	 */
	struct NodeData* get(std::string ID);

	/**
	 * Insertion by index. Takes a Data struct, adds it to the
	 * linked list and maps its address to a key.
	 * Use indices 0 for front and -1 for end.
	 *
	 * @param ID 		take in the key user wants to associate with the data being inserted.
	 * @param nodeData 	is the initialized Data struct containing data to be inserted.
	 * @param index 	is the index where the new data will be inserted.
	 * @return 			0 for success, 1 for nodeID not unique, 2 index out of range.
	 */
	int insByIndex(std::string nodeID, struct NodeData nodeData, int index);

	/**
	 * Insertion by ID inserts the Data struct before the
	 * object mapped by the insID.
	 *
	 * @param ID 		takes in the key user wants to associate with the data being inserted.
	 * @param nodeData 	the initialized Data struct containing data to be inserted.
	 * @param targetID 	the key of a stored data where the new data will be inserted.
	 * @return 			0 for success, 1 for nodeID not unique, 2 targetID out of range.
	 */
	int insByID(std::string nodeID, struct NodeData nodeData, std::string targetID);

	/**
	 * Delete a mapping by index.
	 *
	 * @param index 	to be deleted.
	 * @return 			0 for success, 1 for insertion failure, 2 for deletion failure.
	 */
	int delByIndex(int index);

	/**
	 * Delete a mapping by key. Note: key to data mapping is unique.
	 *
	 * @param ID	the key of the data to be deleted.
	 * @return 		0 for success, 1 for failure.
	 */
	int delByID(std::string ID);

	/**
	 * Delete all mappings.
	 *
	 * @return 		0 for success, 1 for failure (at least 1 filter was not deleted.)
	 */
	int delAll();

	/* ==========================================================================
	 * SUPPLEMENTS
	 * ==========================================================================
	 */

	/**
	 * Get the list of ID
	 *
	 * @return 		the vector of IDs representing the sequence of data stored in the linked list.
	 */
	std::vector<std::string> getList();

	/**
	 * Looks for existing key IDs
	 *
	 * @param ID	the key to find.
	 * @return 		0 for no key, 1 for yes key exists.
	 */
	int find(std::string ID);

	/**
	 * Update the number of nodes stored in the list and return the value.
	 *
	 * @return 		number of nodes stored.
	 */
	int getCount();
};

#endif /* IDHASHER_H_ */
