/*
 * Controller.h
 *
 *  Created on: Mar 12, 2015
 *      Author: ed
 */

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include <iostream>
#include <stdlib.h>

using namespace std;

//Mode not needed
//we have to find out what the command is
//controller only does event handling -> list of if statements determining what to excute
//command structure & task class

class Controller{
public:
    //constructor for the controller class
    Controller(Model *_modelpointer, Mode *_modepointer, string _command){
        sub_model=_modelpointer;
        current_mode=_modepointer;
        command=_command;
    }
    //Destructor to free pointers
    ~Controller(){
        //free(sub_model);
        //free(current_mode);
    }

    //need a handle event function

    

private:
    //Model Pointer
    Model *sub_model;
    Mode *current_mode;
    string command;
    
    //Variables for thrust an[d angles
    float x_thrust, y_thrust, z_thrust;
    float pitch, yaw, roll;
    
};



#endif /* SRC_CONTROLLER_H_ */