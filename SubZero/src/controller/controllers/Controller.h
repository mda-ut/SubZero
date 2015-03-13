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
        free(sub_model);
        free(current_mode);
    }
    
    //movement commands
    void move_forward();
    void move_backward();
    void move_right();
    void move_left();
    
    //angle commands
    void change_pitch();
    void change_yaw();
    void change_roll();
    
    
private:
    //Model Pointer
    Model *sub_model;
    Mode *current_mode;
    string command;
    
    //Variables for thrust and angles
    float x_thrust, y_thrust, z_thrust;
    float pitch, yaw, roll;
    
    void start_motor0();
    void start_motor1();
    void start_motor2();
    void start_motor3();
    void start_motor4();
    void start_motor5();
    void start_motor6();
    void start_motor7();
    
};



#endif /* SRC_CONTROLLER_H_ */