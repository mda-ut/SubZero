/*
 * IDHasher.cpp
 *
 *  Created on: Mar 14, 2015
 *      Author: ahsueh1996
 */

#include "IDHasher.h"

/* ==========================================================================
 * CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */

IDHasher::IDHasher() {
	this->count = 0;
	this->linkedListFront = nullptr;
	this->linkedListRear = nullptr;
	this->dictionary = new std::map<std::string, struct Node*>;
	// Special keys
	this->dictionary["FRONT"] = nullptr;
	this->dictionary["REAR"] = nullptr;
}

IDHasher::~IDHasher() {
	this->delAll();
	delete(this->dictionary);
}

/* ==========================================================================
 * BASIC ADT METHODS
 * ==========================================================================
 */

struct NodeData* IDHasher::get(std::string ID) {
	if (this->dictionary.size > 0 && this->dictionary.count(ID) > 0)
		return this->dictionary[ID];
	else
		return nullptr;
}

int IDHasher::ins(std::string nodeID, struct NodeData nodeData, int index) {
	struct Node *newNode, *currNode;
	int i;

	currNode = this->linkedListFront;

	// Special cases
	if (index == 0)
		return this->ins(nodeID,nodeData,"FRONT");
	else if (index == -1)
		return this->ins(nodeID,nodeData,"REAR");

	// Traverse linked list
	for (i=0;i<index;i++)
	{
		if (currNode == nullptr)
			return 1;
		currNode = currNode->nxt;
	}

	 return this->ins(nodeID,nodeData,currNode->nodeID);
}

int IDHasher::ins(std::string nodeID, struct NodeData nodeData, std::string targetID) {
	struct Node *newNode, *currNode;

	// Check out of range
	if (this->dictionary.count(targetID) == 0)
		return 1;
	// Check unique ID
	if (this->dictionary.count(nodeID) != 0)
		return 2;


	// Initialize newNode pointer
	newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->nodeData = nodeData;
	newNode->nodeID = nodeID;

	// Different cases of insertion
	if (targetID == "FRONT")
	{
		currNode = this->linkedListFront;
		this->linkedListFront = newNode;

		if (currNode != nullptr)
			currNode->prv = newNode;
		else
			this->linkedListRear = newNode;
		newNode->nxt = currNode;
		newNode->prv = nullptr;
	}
	else if (targetID == "REAR")
	{
		currNode = this->linkedListRear;
		this->linkedListRear = newNode;

		if (currNode != nullptr)
			currNode->nxt = newNode;
		else
			this->linkedListFront = newNode;
		newNode->nxt = nullptr;
		newNode->prv = currNode;
	}
	else
	{
		currNode = this->dictionary[targetID];

		if (currNode == nullptr)
			return 3;

		newNode->nxt = currNode;
		if (currNode->prv != nullptr)
			currNode->prv->nxt = newNode;
		else
			this->linkedListFront = newNode;

		newNode->prv = currNode->prv;
		currNode->prv = newNode;
	}

	// Register key pair to dictionary
	this->dictionary[nodeID] = newNode;
	this->count++;
	return 0;
}

int IDHasher::del(int index) {
	struct Node *currNode;
	int i;

	currNode = this->linkedListFront;

	// Traverse linked list
	for (i=0;i<index;i++)
	{
		if (currNode == nullptr)
			return 1;
		currNode = currNode->nxt;
	}
	return this->del(currNode->nodeID);
}

int IDHasher::del(std::string targetID) {
	struct Node *currNode;

	// Check key range
	if (this->dictionary.count(targetID) == 0)
		return 1;

	// Different cases of deletion
	if (targetID == "FRONT")
	{
		currNode = this->linkedListFront;
		this->linkedListFront = currNode->nxt;
	}
	else if (targetID == "REAR")
	{
		currNode = this->linkedListRear;
		this->linkedListRear = currNode->prv;
	}
	else
	{
		currNode = this->dictionary[targetID];

		if (currNode == nullptr)
			break;

		if (currNode->prv != nullptr)
			currNode->prv->nxt = currNode->nxt;
		else
			this->linkedListFront = currNode->nxt;

		if (currNode->nxt != nullptr)
			currNode->nxt->prv = currNode->prv;
		else
			this->linkedListRear = currNode->prv;
	}

	// Free node
	free(currNode);

	// Unregister from dictionary
	this->dictionary.erase(targetID);

	// Confirmation
	if (this->dictionary.count(targetID) != 0)
		return 2;
	this->count--;
	return 0;
}

int IDHasher::delAll() {
	int count = this->count + 10;
	while (this->count != 0)
	{
		this->del("FRONT");
		if (count < 0)
			return 1;
	}
	return 0;
}

/* ==========================================================================
 * SUPPLEMENTS
 * ==========================================================================
 */

std::vector<std::string> IDHasher::getList() {
	std::vector<std::string> list;
	struct Node *currNode = this->linkedListFront;

	// Traverse linked list and store ID
	while (currNode != nullptr)
	{
		list.push_back(currNode->nodeID);
		currNode = currNode->nxt;
	}

	return list;
}

int IDHasher::find(std::string nodeID) {
	return this->dictionary.count(nodeID);
}

int IDHasher::getCount() {
	return this->count;
}
