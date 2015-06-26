/*
 * Main.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "util/Logger.h"
#include <string>
#include "view/menu.h"
#include "controller/controllers/Controller.h"
#include <QApplication>
#include <iostream>

#include "../test/CollectionTEST.h"
#include "model/state/StateTester.h"

using namespace std;

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("Logger initialized.");	
//	QApplication app(argc, argv);
//    Menu* newMenu = new Menu;
//    newMenu->show();

///    newMenu.paintEvent();

//    CollectionTEST::runDataAndFilterManagerCollection();
    CollectionTEST::runFilterCollection(); //commented a crash line in here... uncomment to reproduce

//	StateTester::run();

    Logger::close();
//    delete logTimer;

	return 0;//app.exec();
}

