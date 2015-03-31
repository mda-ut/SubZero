/*
 * Controller.h
 *
 *  Created on: Mar 12, 2015
 *      Author: ed
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <iostream>
#include <stdlib.h>

using namespace std;

//Mode not needed
//we have to find out what the command is
//controller only does event handling -> list of if statements determining what to execute
//command structure & task class
#include <list>

class Controller{
public:
	/**
	 *  Constructor
	 *  @param modelPointer a pointer to the list of models
	 */

    Controller(list <Model> *model);


    /**
     * Destructor
     */

    ~Controller();

private:
    //Model Pointer
    list<Model> *sub_model;
    
};



#endif /* SRC_CONTROLLER_H_ */
