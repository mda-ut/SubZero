/*
 * SubZero.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: mda
 */

#include "SubZero.h"
#include "scripts.h"
#include <QCoreApplication>

int SubZero::ctr = 0;
volatile int signal_quit = 0;

SubZero::SubZero(std::vector<Model *> models_, View *view_, Controller *controller_) {
    models = models_;
    view = view_;
    controller = controller_;
}

SubZero::~SubZero() {
    for (auto& model : models) {
        delete model;
    }
    delete view;
    delete controller;
}

void SubZero::init() {
    init_signal_handler();
    //TODO: Add error handling here when initializing
//    models[2]->initialize();//start fpga connection first, most likely to crash
    models[0]->initialize();
//    models[1]->initialize();
    controller->initialize();
    view->initialize_VC_Connection(controller);//Connect the controller to the view
    view->show();
}

void SubZero::run() {
    while(controller->isRunning()) {
        for (auto& model : models) {
            model->dataTransfer();
            //ctr++;
        }
        QCoreApplication::processEvents();
    }
    view->close();
}
