/*
 * Task.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef TASK_H_
#define TASK_H_

class Task {
public:
	Task();
	virtual ~Task();

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
   	void start_motor0();
    void start_motor1();
    void start_motor2();
    void start_motor3();
    void start_motor4();
    void start_motor5();
    void start_motor6();
    void start_motor7();
};

#endif /* TASK_H_ */
