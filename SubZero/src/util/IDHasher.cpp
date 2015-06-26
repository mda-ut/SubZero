/*
 * IDHasher.cpp
 *
 *  Created on: Mar 14, 2015
 *      Author: ahsueh1996
 */

#include "IDHasher.h"

/* ==========================================================================
 * NODE AND NODE DATA
 * ==========================================================================
 */

Node::Node() {
	this->nxt = 0;
	this->prv = 0;
	this->nodeData = 0;
	this->nodeID = "newNode";
}

Node::~Node() {
	if (this->nodeData != 0)
		delete this->nodeData;
}

NodeData::NodeData() {
	this->data = "";
	this->filter = 0;
}

NodeData::~NodeData() {
	// Delete class objs
	if (this->filter != 0)
		delete this->filter;
}


/* ==========================================================================
 * CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */

IDHasher::IDHasher() {
	this->count = 0;
	this->linkedListFront = 0;
	this->linkedListRear = 0;
//	this->dictionary = *new std::map<std::string, struct Node*>;
	// Special keys
	this->dictionary["FRONT"] = 0;
	this->dictionary["REAR"] = 0;
}

IDHasher::~IDHasher() {
	this->delAll();
	this->dictionary.erase("FRONT");
	this->dictionary.erase("REAR");
	//delete &this->dictionary; // I can't seem to delete the dictionary?
}

/* ==========================================================================
 * BASIC ADT METHODS
 * ==========================================================================
 */

NodeData* IDHasher::get(std::string ID) {
	if (this->dictionary.size() > 0 && this->dictionary.count(ID) > 0) {
			Node* node = this->dictionary[ID];
			if (node == 0)
				return 0;
			else
				return node->nodeData;
	}
	else
		return 0;
}

int IDHasher::insByIndex(std::string nodeID, struct NodeData* nodeData, int index) {
	Node *currNode;
	int i;

	currNode = this->linkedListFront;

	// Special cases
	if (index == 0)
		return this->insByID(nodeID,nodeData,"FRONT");
	else if (index == -1 || index >= this->count)
		return this->insByID(nodeID,nodeData,"REAR");

	if (index < 0)
		return 1;

	// Traverse linked list
	for (i=0;i<index;i++)
	{
		if (currNode == 0)
			return 1;
		currNode = currNode->nxt;
	}

	 return this->insByID(nodeID,nodeData,currNode->nodeID);
}

int IDHasher::insByID(std::string nodeID, struct NodeData* nodeData, std::string targetID) {
	Node *newNode, *currNode;

	// Check out of range
	if (this->dictionary.count(targetID) == 0)
		return 1;
	// Check unique ID
	if (this->dictionary.count(nodeID) != 0)
		return 2;


	// Initialize newNode pointer
	newNode = this->createNode();
	newNode->nodeData = nodeData;
	newNode->nodeID = nodeID;

	// Different cases of insertion
	if (targetID == "FRONT")
	{
		currNode = this->linkedListFront;
		this->linkedListFront = newNode;

		if (currNode != 0)
			currNode->prv = newNode;
		else
			this->linkedListRear = newNode;
		newNode->nxt = currNode;
		newNode->prv = 0;
	}
	else if (targetID == "REAR")
	{
		currNode = this->linkedListRear;
		this->linkedListRear = newNode;

		if (currNode != 0)
			currNode->nxt = newNode;
		else
			this->linkedListFront = newNode;
		newNode->nxt = 0;
		newNode->prv = currNode;
	}
	else
	{
		currNode = this->dictionary[targetID];

		if (currNode == 0)
			return 3;

		newNode->nxt = currNode;
		if (currNode->prv != 0)
			currNode->prv->nxt = newNode;
		else
			this->linkedListFront = newNode;

		newNode->prv = currNode->prv;
		currNode->prv = newNode;
	}
	// Update FRONT & BACK
	this->dictionary["FRONT"] = this->linkedListFront;
	this->dictionary["REAR"] = this->linkedListRear;

	// Register key pair to dictionary
	this->dictionary[nodeID] = newNode;
	this->count++;
	return 0;
}

int IDHasher::delByIndex(int index) {
	struct Node *currNode;
	int i;

	currNode = this->linkedListFront;

	// Special Case
	if (index == 0)
		return this->delByID("FRONT");
	else if (index == -1)
		return this->delByID("REAR");

	if (index < 0)
		return 1;

	// Traverse linked list
	for (i=0;i<index;i++)
	{
		if (currNode == 0)
			return 1;
		currNode = currNode->nxt;
	}
	return this->delByID(currNode->nodeID);
}

int IDHasher::delByID(std::string targetID) {
	struct Node *currNode;

	// Check key range
	if (this->dictionary.count(targetID) == 0)
		return 1;

	// Different cases of deletion
	if (targetID == "FRONT")
	{
		currNode = this->linkedListFront;
		this->linkedListFront = currNode->nxt;
		if (currNode->nxt != 0)
			currNode->nxt->prv = 0;
		targetID = currNode->nodeID;
	}
	else if (targetID == "REAR")
	{
		currNode = this->linkedListRear;
		this->linkedListRear = currNode->prv;
		if (currNode->prv != 0)
			currNode->prv->nxt = 0;
		targetID = currNode->nodeID;
	}
	else
	{
		currNode = this->dictionary[targetID];

		// Do only if currNode is not pointing to null.
		if (currNode != 0)
		{
			if (currNode->prv != 0)
				currNode->prv->nxt = currNode->nxt;
			else
				this->linkedListFront = currNode->nxt;

			if (currNode->nxt != 0)
				currNode->nxt->prv = currNode->prv;
			else
				this->linkedListRear = currNode->prv;
		}
	}

	// Delete the node
	delete currNode;

	// Update FRONT & BACK
	this->dictionary["FRONT"] = this->linkedListFront;
	this->dictionary["REAR"] = this->linkedListRear;

	// Unregister from dictionary
	this->dictionary.erase(targetID);

	// Confirmation
	if (this->dictionary.count(targetID) != 0)
		return 2;
	this->count--;
	return 0;
}

int IDHasher::delAll() {
	int count = this->count;
	while (count > 0)
	{
		this->delByID("FRONT");
		count = this->count;
		if (count < 0)
			return 1;
	}
	return 0;
}

/* ==========================================================================
 * SUPPLEMENTS
 * ==========================================================================
 */

std::vector<std::string> IDHasher::getNodeIDList() {
	std::vector<std::string> list;
	struct Node* currNode = this->linkedListFront;

	// Traverse linked list and store ID
	while (currNode != 0)
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

Node* IDHasher::getFront() {
	return this->linkedListFront;
}

Node* IDHasher::getRear() {
	return this->linkedListRear;
}

Node* IDHasher::createNode() {
	return new Node;
}

NodeData* IDHasher::createNodeData() {
	return new NodeData;
}
