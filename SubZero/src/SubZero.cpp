/*
 * SubZero.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: mda
 */

#include "SubZero.h"
#include <QCoreApplication>

int SubZero::ctr = 0;

SubZero::SubZero(std::vector<Model *> models_, View *view_, Controller *controller_) {
    models = models_;
    view = view_;
    controller = controller_;
}

SubZero::~SubZero() {
    for (auto& model : models) {
        delete model;
    }
    delete controller;
    delete view;

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

    while(ctr < 5) {
        for (auto& model : models) {
            if(model->dataTransfer()) {
                model->notifyObserver();
                //ctr++;
            }
        }
        QCoreApplication::processEvents();
    }
    view->close();
}
