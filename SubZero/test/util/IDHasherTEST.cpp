/*
 * IDHasherTEST.cpp
 *
 *  Created on: May 8, 2015
 *      Author: ahsueh1996
 */

#include "IDHasherTEST.h"

/* TEMPLATE
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	if (fail > 0)
		Logger::warn("  TEST FAILED: _______");
	Logger::trace("==============================");
	Logger::close();
	return fail;
 */

int IDHasherTEST::runUnits() {
	int res;
	Logger::trace("Running all unit tests for IDHasher");
	Logger::trace("==============================");
	res += T_Constructor();
	res += T_get();
	res += T_insByIndex();
	res += T_insByID();
	res += T_delByIndex();
	res += T_delByID();
	res += T_delAll();
	//res += T_getNodeIDList();
	Logger::trace("==============================");
	if (res != 0)
		Logger::warn(StringTools::intToStr(res)+" warning(s) in unit tests");
	Logger::trace("Unit testing complete");
	return res;
}


/* ==========================================================================
 * CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */

int IDHasherTEST::T_Constructor() {
	int fail = 0;

	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	Logger::trace("Testing IDHasher constructor:");
	Logger::trace(" Constructing...");
	IDHasher* hash = new IDHasher;
	Logger::trace("  Complete.");
	Logger::trace(" Accessing public variables...");
	Logger::trace("  Complete.");
	Logger::trace(" Accessing initialized parameters...");
	Logger::trace("  Using getCount(), count: " + StringTools::intToStr(hash->getCount()));
	if (hash->getCount() != 0)
		fail += 1;
	Logger::trace("  Using getFront(), linkedListFront: ");
	if (hash->getFront() == 0)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok: Front node initialize");
		fail += 1;
	}
	Logger::trace("  Using getRear(), linkedListRear: ");
	if (hash->getRear() == 0)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok: Rear node initialize");
		fail += 1;
	}
	Logger::trace("  Using getByID() for \"FRONT\" and \"REAR\": ");
	if (hash->find("FRONT") == 1 && hash->find("REAR") == 1)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok: FRONT/REAR key not found");
		fail += 1;
	}
	Logger::trace("  Complete.");
	Logger::trace(" Deleting IDHasher...");
	delete hash;
	Logger::trace("Testing complete.");

	if (fail > 0)
		Logger::warn("  TEST FAILED: IDHahser constructor");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

int IDHasherTEST::T_Destructor() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	Logger::trace("==============================");
	Logger::close();
	return fail;
}

/* ==========================================================================
 * BASIC ADT METHODS
 * ==========================================================================
 */

int IDHasherTEST::T_get() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	IDHasher* hash = new IDHasher;

	hash->get("FRONT");
	Logger::trace("Testing get(string ID):");
	Logger::trace(" Using newNodeData...");
	NodeData* nd = hash->createNodeData();
	Logger::trace(" Initializing nodeData to \"hello world\"...");
	nd->data = "hello world";
	Logger::trace(" Using insByID() to insert under ID \"myNode\"...");
	hash->insByID("myNode",nd,"FRONT");
	Logger::trace(" Accessing using ID \"myNode\"...");
	if (hash->get("myNode")->data == "hello world")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok: access by custom ID failed");
		fail += 1;
	}
	Logger::trace(" Accessing using FRONT keyword...");
	if (hash->get("FRONT")->data == "hello world")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok: access by FRONT failed");
		fail += 1;
	}
	Logger::trace(" Accessing using REAR keyword...");
	if (hash->get("REAR")->data == "hello world")
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok: access by REAR failed");
		fail += 1;
	}
	Logger::trace("Testing complete.");
	Logger::trace(" Deleting IDHasher...");
	delete hash;

	if (fail > 0)
		Logger::warn("  TEST FAILED: IDHahser get()");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

int IDHasherTEST::T_insByIndex() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	IDHasher* hash = new IDHasher;

	Logger::trace("Testing insByIndex():");
	Logger::trace(" Insertion...");
	Logger::trace("  Inserting element 2 to location 2...");
	NodeData* nd2 = hash->createNodeData();
	nd2->data = "2";
	hash->insByIndex("2",nd2,2);
	Logger::trace("  Inserting element 0 to location 0...");
	NodeData* nd0 = hash->createNodeData();
	nd0->data = "0";
	hash->insByIndex("0",nd0,0);
	Logger::trace("  Inserting element 1 to location 1...");
	NodeData* nd1 = hash->createNodeData();
	nd1->data = "1";
	hash->insByIndex("1",nd1,1);
	Logger::trace("  Inserting element 3 to location -1...");
	NodeData* nd3 = hash->createNodeData();
	nd3->data = "3";
	hash->insByIndex("3",nd3,-1);
	Logger::trace(" Complete.");
	Logger::trace(" Order recall using getFront()...");
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	std::string res = nd0->data+nd1->data+nd2->data+nd3->data;
	Logger::trace("    "+res);
	if (res == "0123")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match");
	}
	Logger::trace(" Try insert out of range...");
	Logger::trace(" Inserting element -10 to index -10...");
	NodeData* nd4 = hash->createNodeData();
	nd4->data = "-10";
	res = StringTools::intToStr(hash->insByIndex("-10",nd4,-10));
	Logger::trace(" Order recall using getFront()...");
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	nd4->data = "";
	if (hash->getFront()->nxt->nxt->nxt->nxt != 0)
		nd4 = hash->getFront()->nxt->nxt->nxt->nxt->nodeData;
	res = nd0->data+nd1->data+nd2->data+nd3->data+nd4->data + ";error code "+res;
	Logger::trace("    "+res);
	if (res == "0123;error code 1")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match/error not reported");
	}
	Logger::trace(" Try insert with non unique nodeID...");
	Logger::trace(" Inserting element 4 to index -1 under key \"3\"...");
	nd4->data = "4";
	res = StringTools::intToStr(hash->insByIndex("3",nd4,-1));
	nd4->data = "";
	if (hash->getFront()->nxt->nxt->nxt->nxt != 0)
		nd4 = hash->getFront()->nxt->nxt->nxt->nxt->nodeData;
	res = nd0->data+nd1->data+nd2->data+nd3->data+nd4->data + ";error code "+res;
	Logger::trace("    "+res);
	if (res == "0123;error code 2")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match/error not reported");
	}
	Logger::trace("Testing Complete.");
	Logger::trace("Deleting hasher...");
	delete hash;

	if (fail > 0)
		Logger::warn("  TEST FAILED: insByIndex()");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

int IDHasherTEST::T_insByID() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	IDHasher* hash = new IDHasher;

	Logger::trace("Testing insByID():");
	Logger::trace(" Insertion...");
	Logger::trace("  Inserting element \"quick\" to FRONT...");
	NodeData* nd0 = hash->createNodeData();
	nd0->data = "quick";
	hash->insByID("0",nd0,"FRONT");
	Logger::trace("  Inserting element \"jumped\" to REAR...");
	NodeData* nd1 = hash->createNodeData();
	nd1->data = "jumped";
	hash->insByID("1",nd1,"REAR");
	Logger::trace("  Inserting element \"fox\" before \"jumped\"...");
	NodeData* nd2 = hash->createNodeData();
	nd2->data = "fox";
	hash->insByID("2",nd2,"1");
	Logger::trace("  Inserting element \"brown\" before \"fox\"...");
	NodeData* nd3 = hash->createNodeData();
	nd3->data = "brown";
	hash->insByID("3",nd3,"2");
	Logger::trace(" Complete.");
	Logger::trace(" Order recall using getFront()...");
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	std::string res = nd0->data+" "+nd1->data+" "+nd2->data+" "+nd3->data;
	Logger::trace("    "+res);
	if (res == "quick brown fox jumped")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match");
	}
	Logger::trace(" Try insert out of range...");
	Logger::trace(" Inserting element \"?\" to targetID \"bogus\"...");
	NodeData* nd4 = hash->createNodeData();
	nd4->data = "?";
	res = StringTools::intToStr(hash->insByID("4",nd4,"bogus"));
	Logger::trace(" Order recall using getFront()...");
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	nd4->data = "";
	if (hash->getFront()->nxt->nxt->nxt->nxt != 0)
		nd4 = hash->getFront()->nxt->nxt->nxt->nxt->nodeData;
	res = nd0->data+" "+nd1->data+" "+nd2->data+" "+nd3->data+" "+nd4->data + ";error code "+res;
	Logger::trace("    "+res);
	if (res == "quick brown fox jumped ;error code 1")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match/error not reported");
	}
	Logger::trace(" Try insert with non unique nodeID...");
	Logger::trace(" Inserting element \"dirty\" before \"brown\" under key \"3\"...");
	nd4->data = "dirty";
	res = StringTools::intToStr(hash->insByID("3",nd4,"2"));
	nd4->data = "";
	if (hash->getFront()->nxt->nxt->nxt->nxt != 0)
		nd4 = hash->getFront()->nxt->nxt->nxt->nxt->nodeData;
	res = nd0->data+" "+nd1->data+" "+nd2->data+" "+nd3->data+" "+nd4->data + ";error code "+res;
	Logger::trace("    "+res);
	if (res == "quick brown fox jumped ;error code 2")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match/error not reported");
	}
	Logger::trace("Testing Complete.");
	Logger::trace("Deleting hasher...");
	delete hash;

	if (fail > 0)
		Logger::warn("  TEST FAILED: insByID()");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

int IDHasherTEST::T_delByIndex() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	IDHasher* hash = new IDHasher;

	Logger::trace("Testing delByIndex():");
	Logger::trace(" Using insByIndex...");
	//Logger::trace("  Inserting element 2 to location 2...");
	NodeData* nd2 = hash->createNodeData();
	nd2->data = "2";
	hash->insByIndex("2",nd2,2);
	//Logger::trace("  Inserting element 0 to location 0...");
	NodeData* nd0 = hash->createNodeData();
	nd0->data = "0";
	hash->insByIndex("0",nd0,0);
	//Logger::trace("  Inserting element 1 to location 1...");
	NodeData* nd1 = hash->createNodeData();
	nd1->data = "1";
	hash->insByIndex("1",nd1,1);
	//Logger::trace("  Inserting element 3 to location -1...");
	NodeData* nd3 = hash->createNodeData();
	nd3->data = "3";
	hash->insByIndex("3",nd3,-1);
	Logger::trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	std::string res = nd0->data+nd1->data+nd2->data+nd3->data;
	Logger::trace("    "+res);
	if (res == "0123")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match");
	}
	Logger::trace(" Deleting index 0...");
	hash->delByIndex(0);
	Logger::trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	res = nd0->data+nd1->data+nd2->data;
	Logger::trace("    "+res);
	if (res == "123")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match");
	}
	Logger::trace(" Deleting index -1...");
	hash->delByIndex(-1);
	Logger::trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	res = nd0->data+nd1->data;
	Logger::trace("    "+res);
	if (res == "12")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match");
	}
	Logger::trace(" Deleting index 1...");
	hash->delByIndex(1);
	Logger::trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	res = nd0->data;
	Logger::trace("    "+res);
	if (res == "1")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match");
	}
	Logger::trace(" Try deleting out of range...");
	Logger::trace(" Deleting index 10...");
	res = StringTools::intToStr(hash->delByIndex(10));
	Logger::trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	res = nd0->data + ";error code "+res;
	Logger::trace("    "+res);
	if (res == "1;error code 1")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match/error not reported");
	}
	Logger::trace("Testing Complete.");
	Logger::trace("Deleting hasher...");
	delete hash;

	if (fail > 0)
		Logger::warn("  TEST FAILED: delByIndex()");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

int IDHasherTEST::T_delByID() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	IDHasher* hash = new IDHasher;

	Logger::trace("Testing delByID():");
	Logger::trace(" Using insByIndex...");
	NodeData* nd0,*nd1,*nd2,*nd3;
	nd0 = hash->createNodeData();
	nd1 = hash->createNodeData();
	nd2 = hash->createNodeData();
	nd3 = hash->createNodeData();
	nd0->data = "0";
	nd1->data = "1";
	nd2->data = "2";
	nd3->data = "3";
	hash->insByIndex("0",nd0,-1);
	hash->insByIndex("1",nd1,-1);
	hash->insByIndex("2",nd2,-1);
	hash->insByIndex("3",nd3,-1);
	Logger::trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	std::string res = nd0->data+nd1->data+nd2->data+nd3->data;
	Logger::trace("    "+res);
	if (res == "0123")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match");
	}
	Logger::trace(" Deleting ID \"FRONT\"...");
	hash->delByID("FRONT");
	Logger::trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = hash->createNodeData();
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3->data = "";
	if (hash->getFront()->nxt->nxt->nxt != 0)
		nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	res = nd0->data+nd1->data+nd2->data+nd3->data;
	Logger::trace("    "+res);
	if (res == "123")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match");
	}
	Logger::trace(" Deleting ID \"REAR\"...");
	hash->delByID("REAR");
	Logger::trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = hash->createNodeData(); nd3 = hash->createNodeData();
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2->data = "";
	nd3->data = "";
	if (hash->getFront()->nxt->nxt != 0) {
		nd2 = hash->getFront()->nxt->nxt->nodeData;
		if (hash->getFront()->nxt->nxt->nxt != 0)
			nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	}
	res = nd0->data+nd1->data+nd2->data+nd3->data;
	Logger::trace("    "+res);
	if (res == "12")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match");
	}
	Logger::trace(" Deleting ID \"1\", corresponding to element \"1\"...");
	hash->delByID("1");
	Logger::trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = hash->createNodeData(); nd2 = hash->createNodeData(); nd3 = hash->createNodeData();
	nd0 = hash->getFront()->nodeData;
	nd1->data = "";
	nd2->data = "";
	nd3->data = "";
	if (hash->getFront()->nxt != 0) {
		nd1 = hash->getFront()->nxt->nodeData;
		if (hash->getFront()->nxt->nxt != 0) {
			nd2 = hash->getFront()->nxt->nxt->nodeData;
			if (hash->getFront()->nxt->nxt->nxt != 0)
				nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	}}
	res = nd0->data+nd1->data+nd2->data+nd3->data;
	Logger::trace("    "+res);
	if (res == "2")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match");
	}
	Logger::trace(" Try deleting out of range...");
	Logger::trace(" Deleting ID \"bogus\"...");
	res = StringTools::intToStr(hash->delByID("bogus"));
	Logger::trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = hash->createNodeData(); nd2 = hash->createNodeData(); nd3 = hash->createNodeData();
	nd0 = hash->getFront()->nodeData;
	nd1->data = "";
	nd2->data = "";
	nd3->data = "";
	if (hash->getFront()->nxt != 0) {
		nd1 = hash->getFront()->nxt->nodeData;
		if (hash->getFront()->nxt->nxt != 0) {
			nd2 = hash->getFront()->nxt->nxt->nodeData;
			if (hash->getFront()->nxt->nxt->nxt != 0)
				nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	}}
	res = nd0->data+nd1->data+nd2->data+nd3->data+";error code "+res;
	Logger::trace("    "+res);
	if (res == "2;error code 1")
		Logger::trace("    ok");
	else {
		fail += 1;
		Logger::warn("    NOT ok: order recall miss-match/error not reported");
	}
	Logger::trace("Testing Complete.");
	Logger::trace("Deleting hasher...");
	delete hash;

	if (fail > 0)
		Logger::warn("  TEST FAILED: delByID()");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

int IDHasherTEST::T_delAll() {
	int fail = 0;
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("==============================");

	IDHasher* hash = new IDHasher;

	Logger::trace("Testing delAll():");
	Logger::trace(" Inserting...");
	Logger::trace("  Register key \"katana\"...");
	NodeData* nd0 = hash->createNodeData();
	hash->insByID("katana",nd0,"REAR");
	Logger::trace("  Register key \"monerean\"...");
	NodeData* nd1 = hash->createNodeData();
	hash->insByID("monerean",nd1,"REAR");
	Logger::trace("  Register key \"gintoki\"...");
	NodeData* nd2 = hash->createNodeData();
	hash->insByID("gintoki",nd2,"REAR");
	Logger::trace("  Register key \"sadaharu\"...");
	NodeData* nd3 = hash->createNodeData();
	hash->insByID("sadaharu",nd3,"REAR");
	Logger::trace(" Deleting all...");
	hash->delAll();
	Logger::trace(" Try find registered keys, using find()...");
	Logger::trace("  \"katana\"...");
	if (hash->find("katana")==0)
		Logger::trace("    ok, key not found");
	else {
		Logger::warn("    NOT ok, key not deleted");
		fail += 1;
	}
	Logger::trace("  \"monerean\"...");
	if (hash->find("monerean")==0)
		Logger::trace("    ok, key not found");
	else {
		Logger::warn("    NOT ok, key not deleted");
		fail += 1;
	}
	Logger::trace("  \"gintoki\"...");
	if (hash->find("gintoki")==0)
		Logger::trace("    ok, key not found");
	else {
		Logger::warn("    NOT ok, key not deleted");
		fail += 1;
	}
	Logger::trace("  \"sadaharu\"...");
	if (hash->find("sadaharu")==0)
		Logger::trace("    ok, key not found");
	else {
		Logger::warn("    NOT ok, key not deleted");
		fail += 1;
	}
	Logger::trace("  \"FRONT\"...");
	if (hash->find("FRONT")>=1)
		Logger::trace("    ok, key found");
	else {
		Logger::warn("    NOT ok, key deleted");
		fail += 1;
	}
	Logger::trace("  \"REAR\"...");
	if (hash->find("REAR")>=1)
		Logger::trace("    ok, key found");
	else {
		Logger::warn("    NOT ok, key deleted");
		fail += 1;
	}
	Logger::trace(" Checking count == 0? ...");
	if (hash->getCount() == 0)
		Logger::trace("    ok");
	else {
		Logger::warn("    NOT ok, count not zero");
	}
	Logger::trace(" Test Complete.");
	delete hash;

	if (fail > 0)
		Logger::warn("  TEST FAILED: delAll()");
	Logger::trace("==============================");
	Logger::close();
	return fail;
}

int IDHasherTEST::T_getNodeIDList() {
//	int fail = 0;
//	Timer* logTimer = new Timer();
//	Logger::initialize(true, true, logTimer);
//	Logger::trace("==============================");
//
//	IDHasher* hash = new IDHasher;
//
//	Logger::trace("Testing getNodeIDList():");
//	Logger::trace(" Inserting...");
//	Logger::trace("  Register key \"katana\"...");
//	NodeData* nd0 = hash->createNodeData();
//	hash->insByID("katana",nd0,"REAR");
//	Logger::trace("  Register key \"monerean\"...");
//	NodeData* nd1 = hash->createNodeData();
//	hash->insByID("monerean",nd1,"REAR");
//	Logger::trace("  Register key \"gintoki\"...");
//	NodeData* nd2 = hash->createNodeData();
//	hash->insByID("gintoki",nd2,"REAR");
//	Logger::trace("  Register key \"sadaharu\"...");
//	NodeData* nd3 = hash->createNodeData();
//	hash->insByID("sadaharu",nd3,"REAR");
//	Logger::trace(" Getting list...");
//	std::vector<std::string> list = hash->getNodeIDList();
//	std::iterator it = list.iterator;
//
//	Logger::trace(" Test Complete.");
//	delete hash;
//
//	if (fail > 0)
//		Logger::warn("  TEST FAILED: delAll()");
//	Logger::trace("==============================");
//	Logger::close();
//	return fail;
}
