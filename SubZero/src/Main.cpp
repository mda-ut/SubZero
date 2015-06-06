/*
 * Main.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "util/Logger.h"
#include "model/state/StateTester.h"
#include <string>
#include "view/menu.h"
#include <QApplication>

#include "../test/CollectionTEST.h"

using namespace std;

int main(int argc, char** argv) {
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("Logger initialized.");
	
	QApplication app(argc, argv);
    Menu* newMenu = new Menu;
    newMenu->show();
    //newMenu.paintEvent();

    CollectionTEST::runFilterCollection();

	//StateTester::run();

	Logger::close();

	return 0;
}

