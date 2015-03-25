/*
 * IDHasher.cpp
 *
 *  Created on: Mar 14, 2015
 *      Author: ahsueh1996
 */

#include "IDHasher.h"

IDHasher::IDHasher () {

}

struct Data* IDHasher::get(std::string ID) {
	if (this->dictionary.size > 0 && this->dictionary.count(ID) > 0)
		return this->dictionary[ID];
	else
		return nullptr;
}

int IDHasher::ins(std::string ID, struct Data data, int index) {
	struct Node *newNode, *currNode, *prevNode;
	int i;

	if (this->dictionary.count(ID)==0)
		return 1;

	newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;

	if (index == 0)
	{
		newNode->nxt = this->linkedListFront;
		newNode->prv = nullptr;
		this->linkedListFront = newNode;
	}
	else if (index == -1)
	{
		newNode->nxt = nullptr;
		newNode->prv = this->linkedListRear;
		this->linkedListRear = newNode;
	}
	else
	{
		currNode = this->linkedListFront;
		for (i=0;i<index;i++)
		{
			if (currNode == nullptr)
				return 1;
			prevNode = currNode;
			currNode = currNode->nxt;
		}
		newNode->nxt = currNode;
		newNode->prv = prevNode;
	}
	this->dictionary[ID] = newNode;
	return 0;
}


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
