/*
 * SubZero.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: mda
 */

#include "SubZero.h"
#include <QCoreApplication>

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

void SubZero::initialize() {
    for (auto& model : models) {
        model->initialize();
    }
    controller->initialize();
    view->initialize();
}


View *SubZero::getView() {
    return view;
}

