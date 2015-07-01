/*
 * SubZero.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: mda
 */

#include "SubZero.h"

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
    for (auto& model : models) {
        model->initialize();
    }
    controller->initialize();
    view->initialize_VC_Connection(controller);//Connect the controller to the view
    view->show();
}

void SubZero::run() {
    while(1);
}
