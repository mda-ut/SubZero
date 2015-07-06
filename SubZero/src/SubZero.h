/*
 * SubZero.h
 *
 *  Created on: Jan 8, 2015
 *      Author: mda
 */

#ifndef SUBZERO_H_
#define SUBZERO_H_

#include "model/Model.h"
#include "view/View.h"
#include "controller/controllers/Controller.h"
#include <vector>

class SubZero {
private:
    std::vector<Model*> models;
    View* view;
    Controller* controller;
public:
    static int ctr;
    SubZero(std::vector<Model*> models_, View* view_, Controller* controller_);
	virtual ~SubZero();
    void init();
    void run();
};

#endif /* SUBZERO_H_ */
