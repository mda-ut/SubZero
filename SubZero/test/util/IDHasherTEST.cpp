/*
 * IDHasherTEST.cpp
 *
 *  Created on: May 8, 2015
 *      Author: ahsueh1996
 */

#include "IDHasherTEST.h"

/* TEMPLATE
	int fail = 0;
    logger->trace("==============================");

	if (fail > 0)
        logger->warn("  TEST FAILED: _______");
    logger->trace("==============================");
	return fail;
 */

int IDHasherTEST::runUnits() {
	int res = 0;
    logger->trace("Running all unit tests for: IDHasher");
    logger->trace("==============================");
	res += T_Constructor();
	res += T_get();
	res += T_insByIndex();
	res += T_insByID();
	res += T_delByIndex();
	res += T_delByID();
	res += T_delAll();
	res += T_getNodeIDList();
    logger->trace("==============================");
	if (res != 0)
        logger->warn(StringTools::intToStr(res)+" warning(s) in unit tests");
    logger->trace("Unit testing complete: IDHasher");
    logger->trace("NOTE: all units mem tested");
	return res;
}


/* ==========================================================================
 * CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */

int IDHasherTEST::T_Constructor() {
	int fail = 0;

    logger->trace("==============================");

    logger->trace("Testing IDHasher constructor:");
    logger->trace(" Constructing...");
	IDHasher* hash = new IDHasher;
    logger->trace("  Complete.");
    logger->trace(" Accessing public variables...");
    logger->trace("  Complete.");
    logger->trace(" Accessing initialized parameters...");
    logger->trace("  Using getCount(), count: " + StringTools::intToStr(hash->getCount()));
	if (hash->getCount() != 0)
		fail += 1;
    logger->trace("  Using getFront(), linkedListFront: ");
	if (hash->getFront() == 0)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok: Front node initialize");
		fail += 1;
	}
    logger->trace("  Using getRear(), linkedListRear: ");
	if (hash->getRear() == 0)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok: Rear node initialize");
		fail += 1;
	}
    logger->trace("  Using getByID() for \"FRONT\" and \"REAR\": ");
	if (hash->find("FRONT") == 1 && hash->find("REAR") == 1)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok: FRONT/REAR key not found");
		fail += 1;
	}
    logger->trace("  Complete.");
    logger->trace(" Deleting IDHasher...");
	delete hash;
    logger->trace("Testing complete.");

	if (fail > 0)
        logger->warn("  TEST FAILED: IDHahser constructor");
    logger->trace("==============================");
	return fail;
}

int IDHasherTEST::T_Destructor() {
	int fail = 0;
    logger->trace("==============================");

    logger->trace("==============================");
	return fail;
}

/* ==========================================================================
 * BASIC ADT METHODS
 * ==========================================================================
 */

int IDHasherTEST::T_get() {
	int fail = 0;

    logger->trace("==============================");

	IDHasher* hash = new IDHasher;

	hash->get("FRONT");
    logger->trace("Testing get(string ID):");
    logger->trace(" Using newNodeData...");
	NodeData* nd = hash->createNodeData();
    logger->trace(" Initializing nodeData to \"hello world\"...");
	nd->data = "hello world";
    logger->trace(" Using insByID() to insert under ID \"myNode\"...");
	hash->insByID("myNode",nd,"FRONT");
    logger->trace(" Accessing using ID \"myNode\"...");
	if (hash->get("myNode")->data == "hello world")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok: access by custom ID failed");
		fail += 1;
	}
    logger->trace(" Accessing using FRONT keyword...");
	if (hash->get("FRONT")->data == "hello world")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok: access by FRONT failed");
		fail += 1;
	}
    logger->trace(" Accessing using REAR keyword...");
	if (hash->get("REAR")->data == "hello world")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok: access by REAR failed");
		fail += 1;
	}
    logger->trace("Testing complete.");
    logger->trace(" Deleting IDHasher...");
	delete hash;

	if (fail > 0)
        logger->warn("  TEST FAILED: IDHahser get()");
    logger->trace("==============================");
	return fail;
}

int IDHasherTEST::T_insByIndex() {
	int fail = 0;
    logger->trace("==============================");

	IDHasher* hash = new IDHasher;

    logger->trace("Testing insByIndex():");
    logger->trace(" Insertion...");
    logger->trace("  Inserting element 2 to location 2...");
	NodeData* nd2 = hash->createNodeData();
	nd2->data = "2";
	hash->insByIndex("2",nd2,2);
    logger->trace("  Inserting element 0 to location 0...");
	NodeData* nd0 = hash->createNodeData();
	nd0->data = "0";
	hash->insByIndex("0",nd0,0);
    logger->trace("  Inserting element 1 to location 1...");
	NodeData* nd1 = hash->createNodeData();
	nd1->data = "1";
	hash->insByIndex("1",nd1,1);
    logger->trace("  Inserting element 3 to location -1...");
	NodeData* nd3 = hash->createNodeData();
	nd3->data = "3";
	hash->insByIndex("3",nd3,-1);
    logger->trace(" Complete.");
    logger->trace(" Order recall using getFront()...");
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	std::string res = nd0->data+nd1->data+nd2->data+nd3->data;
    logger->trace("    "+res);
	if (res == "0123")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match");
	}
    logger->trace(" Try insert out of range...");
    logger->trace(" Inserting element -10 to index -10...");
	NodeData* nd4 = hash->createNodeData();
	nd4->data = "-10";
	res = StringTools::intToStr(hash->insByIndex("-10",nd4,-10));
    logger->trace(" Order recall using getFront()...");
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	nd4->data = "";
	if (hash->getFront()->nxt->nxt->nxt->nxt != 0)
		nd4 = hash->getFront()->nxt->nxt->nxt->nxt->nodeData;
	res = nd0->data+nd1->data+nd2->data+nd3->data+nd4->data + ";error code "+res;
    logger->trace("    "+res);
	if (res == "0123;error code 1")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match/error not reported");
	}
    logger->trace(" Try insert with non unique nodeID...");
    logger->trace(" Inserting element 4 to index -1 under key \"3\"...");
	nd4->data = "4";
	res = StringTools::intToStr(hash->insByIndex("3",nd4,-1));
	nd4->data = "";
	if (hash->getFront()->nxt->nxt->nxt->nxt != 0)
		nd4 = hash->getFront()->nxt->nxt->nxt->nxt->nodeData;
	res = nd0->data+nd1->data+nd2->data+nd3->data+nd4->data + ";error code "+res;
    logger->trace("    "+res);
	if (res == "0123;error code 2")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match/error not reported");
	}
    logger->trace("Testing Complete.");
    logger->trace("Deleting hasher...");
	delete nd4;
	delete hash;

	if (fail > 0)
        logger->warn("  TEST FAILED: insByIndex()");
    logger->trace("==============================");
	return fail;
}

int IDHasherTEST::T_insByID() {
	int fail = 0;
    logger->trace("==============================");

	IDHasher* hash = new IDHasher;

    logger->trace("Testing insByID():");
    logger->trace(" Insertion...");
    logger->trace("  Inserting element \"quick\" to FRONT...");
	NodeData* nd0 = hash->createNodeData();
	nd0->data = "quick";
	hash->insByID("0",nd0,"FRONT");
    logger->trace("  Inserting element \"jumped\" to REAR...");
	NodeData* nd1 = hash->createNodeData();
	nd1->data = "jumped";
	hash->insByID("1",nd1,"REAR");
    logger->trace("  Inserting element \"fox\" before \"jumped\"...");
	NodeData* nd2 = hash->createNodeData();
	nd2->data = "fox";
	hash->insByID("2",nd2,"1");
    logger->trace("  Inserting element \"brown\" before \"fox\"...");
	NodeData* nd3 = hash->createNodeData();
	nd3->data = "brown";
	hash->insByID("3",nd3,"2");
    logger->trace(" Complete.");
    logger->trace(" Order recall using getFront()...");
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	std::string res = nd0->data+" "+nd1->data+" "+nd2->data+" "+nd3->data;
    logger->trace("    "+res);
	if (res == "quick brown fox jumped")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match");
	}
    logger->trace(" Try insert out of range...");
    logger->trace(" Inserting element \"?\" to targetID \"bogus\"...");
	NodeData* nd4 = hash->createNodeData();
	nd4->data = "?";
	res = StringTools::intToStr(hash->insByID("4",nd4,"bogus"));
    logger->trace(" Order recall using getFront()...");
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	nd4->data = "";
	if (hash->getFront()->nxt->nxt->nxt->nxt != 0)
		nd4 = hash->getFront()->nxt->nxt->nxt->nxt->nodeData;
	res = nd0->data+" "+nd1->data+" "+nd2->data+" "+nd3->data+" "+nd4->data + ";error code "+res;
    logger->trace("    "+res);
	if (res == "quick brown fox jumped ;error code 1")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match/error not reported");
	}
    logger->trace(" Try insert with non unique nodeID...");
    logger->trace(" Inserting element \"dirty\" before \"brown\" under key \"3\"...");
	nd4->data = "dirty";
	res = StringTools::intToStr(hash->insByID("3",nd4,"2"));
	nd4->data = "";
	if (hash->getFront()->nxt->nxt->nxt->nxt != 0)
		nd4 = hash->getFront()->nxt->nxt->nxt->nxt->nodeData;
	res = nd0->data+" "+nd1->data+" "+nd2->data+" "+nd3->data+" "+nd4->data + ";error code "+res;
    logger->trace("    "+res);
	if (res == "quick brown fox jumped ;error code 2")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match/error not reported");
	}
    logger->trace("Testing Complete.");
    logger->trace("Deleting hasher...");
	delete nd4;
	delete hash;

	if (fail > 0)
        logger->warn("  TEST FAILED: insByID()");
    logger->trace("==============================");
	return fail;
}

int IDHasherTEST::T_delByIndex() {
	int fail = 0;
    logger->trace("==============================");

	IDHasher* hash = new IDHasher;

    logger->trace("Testing delByIndex():");
    logger->trace(" Using insByIndex...");
    //logger->trace("  Inserting element 2 to location 2...");
	NodeData* nd2 = hash->createNodeData();
	nd2->data = "2";
	hash->insByIndex("2",nd2,2);
    //logger->trace("  Inserting element 0 to location 0...");
	NodeData* nd0 = hash->createNodeData();
	nd0->data = "0";
	hash->insByIndex("0",nd0,0);
    //logger->trace("  Inserting element 1 to location 1...");
	NodeData* nd1 = hash->createNodeData();
	nd1->data = "1";
	hash->insByIndex("1",nd1,1);
    //logger->trace("  Inserting element 3 to location -1...");
	NodeData* nd3 = hash->createNodeData();
	nd3->data = "3";
	hash->insByIndex("3",nd3,-1);
    logger->trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	std::string res = nd0->data+nd1->data+nd2->data+nd3->data;
    logger->trace("    "+res);
	if (res == "0123")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match");
	}
    logger->trace(" Deleting index 0...");
	hash->delByIndex(0);
    logger->trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	res = nd0->data+nd1->data+nd2->data;
    logger->trace("    "+res);
	if (res == "123")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match");
	}
    logger->trace(" Deleting index -1...");
	hash->delByIndex(-1);
    logger->trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	res = nd0->data+nd1->data;
    logger->trace("    "+res);
	if (res == "12")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match");
	}
    logger->trace(" Deleting index 1...");
	hash->delByIndex(1);
    logger->trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	res = nd0->data;
    logger->trace("    "+res);
	if (res == "1")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match");
	}
    logger->trace(" Try deleting out of range...");
    logger->trace(" Deleting index 10...");
	res = StringTools::intToStr(hash->delByIndex(10));
    logger->trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	res = nd0->data + ";error code "+res;
    logger->trace("    "+res);
	if (res == "1;error code 1")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match/error not reported");
	}
    logger->trace("Testing Complete.");
    logger->trace("Deleting hasher...");
	delete hash;

	if (fail > 0)
        logger->warn("  TEST FAILED: delByIndex()");
    logger->trace("==============================");
	return fail;
}

int IDHasherTEST::T_delByID() {
	int fail = 0;
    logger->trace("==============================");

	IDHasher* hash = new IDHasher;

    logger->trace("Testing delByID():");
    logger->trace(" Using insByIndex...");
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
    logger->trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = 0;
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	std::string res = nd0->data+nd1->data+nd2->data+nd3->data;
    logger->trace("    "+res);
	if (res == "0123")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match");
	}
    logger->trace(" Deleting ID \"FRONT\"...");
	hash->delByID("FRONT");
    logger->trace(" Order recall using getFront()...");
	nd0 = 0; nd1 = 0; nd2 = 0; nd3 = hash->createNodeData();
	nd0 = hash->getFront()->nodeData;
	nd1 = hash->getFront()->nxt->nodeData;
	nd2 = hash->getFront()->nxt->nxt->nodeData;
	nd3->data = "";
	if (hash->getFront()->nxt->nxt->nxt != 0)
		nd3 = hash->getFront()->nxt->nxt->nxt->nodeData;
	res = nd0->data+nd1->data+nd2->data+nd3->data;
	delete nd3;
    logger->trace("    "+res);
	if (res == "123")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match");
	}
    logger->trace(" Deleting ID \"REAR\"...");
	hash->delByID("REAR");
    logger->trace(" Order recall using getFront()...");
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
	delete nd2;
	delete nd3;
    logger->trace("    "+res);
	if (res == "12")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match");
	}
    logger->trace(" Deleting ID \"1\", corresponding to element \"1\"...");
	hash->delByID("1");
    logger->trace(" Order recall using getFront()...");
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
	delete nd1;
	delete nd2;
	delete nd3;
    logger->trace("    "+res);
	if (res == "2")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match");
	}
    logger->trace(" Try deleting out of range...");
    logger->trace(" Deleting ID \"bogus\"...");
	res = StringTools::intToStr(hash->delByID("bogus"));
    logger->trace(" Order recall using getFront()...");
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
    logger->trace("    "+res);
	delete nd1;
	delete nd2;
	delete nd3;
	if (res == "2;error code 1")
        logger->trace("    ok");
	else {
		fail += 1;
        logger->warn("    NOT ok: order recall miss-match/error not reported");
	}
    logger->trace("Testing Complete.");
    logger->trace("Deleting hasher...");
	delete hash;

	if (fail > 0)
        logger->warn("  TEST FAILED: delByID()");
    logger->trace("==============================");
	return fail;
}

int IDHasherTEST::T_delAll() {
	int fail = 0;
    logger->trace("==============================");

	IDHasher* hash = new IDHasher;

    logger->trace("Testing delAll():");
    logger->trace(" Inserting...");
    logger->trace("  Register key \"katana\"...");
	NodeData* nd0 = hash->createNodeData();
	hash->insByID("katana",nd0,"REAR");
    logger->trace("  Register key \"monerean\"...");
	NodeData* nd1 = hash->createNodeData();
	hash->insByID("monerean",nd1,"REAR");
    logger->trace("  Register key \"gintoki\"...");
	NodeData* nd2 = hash->createNodeData();
	hash->insByID("gintoki",nd2,"REAR");
    logger->trace("  Register key \"sadaharu\"...");
	NodeData* nd3 = hash->createNodeData();
	hash->insByID("sadaharu",nd3,"REAR");
    logger->trace(" Deleting all...");
	hash->delAll();
    logger->trace(" Try find registered keys, using find()...");
    logger->trace("  \"katana\"...");
	if (hash->find("katana")==0)
        logger->trace("    ok, key not found");
	else {
        logger->warn("    NOT ok, key not deleted");
		fail += 1;
	}
    logger->trace("  \"monerean\"...");
	if (hash->find("monerean")==0)
        logger->trace("    ok, key not found");
	else {
        logger->warn("    NOT ok, key not deleted");
		fail += 1;
	}
    logger->trace("  \"gintoki\"...");
	if (hash->find("gintoki")==0)
        logger->trace("    ok, key not found");
	else {
        logger->warn("    NOT ok, key not deleted");
		fail += 1;
	}
    logger->trace("  \"sadaharu\"...");
	if (hash->find("sadaharu")==0)
        logger->trace("    ok, key not found");
	else {
        logger->warn("    NOT ok, key not deleted");
		fail += 1;
	}
    logger->trace("  \"FRONT\"...");
	if (hash->find("FRONT")>=1)
        logger->trace("    ok, key found");
	else {
        logger->warn("    NOT ok, key deleted");
		fail += 1;
	}
    logger->trace("  \"REAR\"...");
	if (hash->find("REAR")>=1)
        logger->trace("    ok, key found");
	else {
        logger->warn("    NOT ok, key deleted");
		fail += 1;
	}
    logger->trace(" Checking count == 0? ...");
	if (hash->getCount() == 0)
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, count not zero");
	}
    logger->trace(" Test Complete.");
	delete hash;

	if (fail > 0)
        logger->warn("  TEST FAILED: delAll()");
    logger->trace("==============================");
	return fail;
}

int IDHasherTEST::T_getNodeIDList() {
	int fail = 0;
    logger->trace("==============================");

	IDHasher* hash = new IDHasher;

    logger->trace("Testing getNodeIDList():");
    logger->trace(" Inserting...");
    logger->trace("  Register key \"katana\"...");
	NodeData* nd0 = hash->createNodeData();
	hash->insByID("katana",nd0,"REAR");
    logger->trace("  Register key \"monerean\"...");
	NodeData* nd1 = hash->createNodeData();
	hash->insByID("monerean",nd1,"REAR");
    logger->trace("  Register key \"gintoki\"...");
	NodeData* nd2 = hash->createNodeData();
	hash->insByID("gintoki",nd2,"REAR");
    logger->trace("  Register key \"sadaharu\"...");
	NodeData* nd3 = hash->createNodeData();
	hash->insByID("sadaharu",nd3,"REAR");
    logger->trace(" Getting list...");
	std::vector<std::string> list = hash->getNodeIDList();
	std::string res;
	for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++)
		res += " "+*it;
    logger->trace("    "+res);
	if (res == " katana monerean gintoki sadaharu")
        logger->trace("    ok");
	else {
        logger->warn("    NOT ok, list unexpected");
		fail += 1;
	}

    logger->trace(" Test Complete.");
	delete hash;

	if (fail > 0)
        logger->warn("  TEST FAILED: getNodeIDList()");
    logger->trace("==============================");
	return fail;
}
