/*
 * IDHasher.h
 *
 *  Created on: Mar 14, 2015
 *      Author: ahsueh1996
 */

#ifndef IDHASHER_H_
#define IDHASHER_H_
#include <unordered_map>
#include <vector>

struct Node {
	struct Node* nxt;
	struct Node* prv;
	struct Data* data;
};

class IDHasher {
	/*
	 * The IDHasher is an ADT using a combination of map and linked
	 * list to allow user to store and access data via mapping from
	 * a string key (custom user set ID) to the data. Data struct is
	 * left to the user of the ADT to define and is contained in
	 * nodes. Nodes are linked to each other to retain a sequential
	 * ordering (which is otherwise lost in a regular map object).
	 */
public:
	/*
	 * Hash constructor
	 */
	IDHasher ();

	/*
	 * Search and returns a ptr to the data. It should be noted
	 * that the Data struct is a wrapper for the real data being
	 * requested. User of IDHasher could use their definition of
	 * struct Data to return the desired data.
	 *
	 * @return Data*, which is a wrapper class for the "real data."
	 */
	struct Data* get(std::string ID);

	/*
	 * Insertion by index. Takes a Data struct, adds it to the
	 * linked list and maps its address to a key.
	 * Use indices 0 for front and -1 for end.
	 *
	 * @return 0 for success, 1 for failed insertion.
	 */
	int ins(std::string ID, struct Data data, int index);

	/*
	 * Insertion by ID inserts the Data struct before the
	 * object mapped by the insID.
	 *
	 * @return 0 for success, 1 for failed insertion.
	 */
	int ins(std::string ID, struct Data data, std::string insID);

	/*
	 * Delete a mapping by index.
	 *
	 * @return 0 for success, 1 for failure.
	 */
	int del(int index);

	/*
	 * Delete a mapping by key.
	 *
	 * @return 0 for success, 1 for failure.
	 */
	int del(std::string ID);

	/*
	 * Delete all mappings.
	 *
	 * @return 0 for success, 1 for failure (at least 1 filter was not deleted.)
	 */
	int delAll();

	/*
	 * Get the list of ID
	 *
	 * @return the vector of IDs representing the sequence of data stored in the linked list.
	 */
	std::vector<std::string> getList();

private:
	// Dictionary to map ID to nodes in the linked list
	std::map<std::string, struct Node*> dictionary;
	
	// Linked List
	struct Node* linkedListFront = nullptr;
	struct Node* linkedListRear = nullptr;
};

#endif /* IDHASHER_H_ */
