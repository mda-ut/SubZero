/*
 * SubZero.h
 *
 *  Created on: Jan 8, 2015
 *      Author: mda
 */

#ifndef SUBZERO_H_
#define SUBZERO_H_

#include <Model.h>
#include <View.h>
#include <Controller.h>
#include <vector>

class SubZero {
private:
    std::vector<Model*> models;
    View* view;
    Controller* controller;
public:
    SubZero(std::vector<Model*> models_, View* view_, Controller* controller_);
	virtual ~SubZero();
    void init();
    void run();
};

#endif /* SUBZERO_H_ */
