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
#include "controller/controllers/Controller.h"
#include <QApplication>
#include <iostream>

#include "../test/CollectionTEST.h"

using namespace std;

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("Logger initialized.");

    //CollectionTEST::runFilterCollection();
    //Controller* newController = new Controller;
    Menu* newMenu = new Menu;
    //newMenu->show();

    HwInterface* hw = new FPGAInterface(10, 1);

    Logger::close();

    return app.exec();
}

