/*
 * Main.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "util/Logger.h"
#include "view/menu.h"
#include "../test/util/filter/FilterManagerTEST.h"
#include <string>
#include <QApplication>

using namespace std;

int main(int argc, char** argv) {
	Timer* logTimer = new Timer();
	Logger::initialize(true, true, logTimer);
	Logger::trace("Logger initialized.");

	//FilterManagerTEST::runUnits();
	QApplication app(argc, argv);
    Menu* newMenu = new Menu;
    newMenu->show();
    //newMenu.paintEvent();
	Logger::trace("Does this build/run?");

	Logger::close();

	return app.exec();
}

