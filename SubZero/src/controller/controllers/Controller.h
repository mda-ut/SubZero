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

class Controller{
public:
    //constructor for the controller class
    Controller(Model *_modelpointer, string _command);


    //Destructor to free pointers
    ~Controller();

    //need a handle event function

    

private:
    //Model Pointer
    Model *sub_model;
    string command;
    
    //Variables for thrust an[d angles
    float x_thrust, y_thrust, z_thrust;
    float pitch, yaw, roll;
    
};



#endif /* SRC_CONTROLLER_H_ */
