/*
 * TaskFactory.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: ed
 */

#include "TaskFactory.h"

TaskFactory::TaskFactory() {
    // TODO Auto-generated constructor stub

}

/*
BaseTask* TaskFactory::newTask(const std::string input){
    BaseTask* newTask;

    switch (input)

    default:

    return newTask;
}
*/

TurnTask* TaskFactory::createTurnTask(Model* fpgaModel, int& targetYaw, int delta) {
    return new TurnTask(fpgaModel, targetYaw, delta);
}

PowerTask* TaskFactory::createPowerTask(Model* fpgaModel, bool powerOn, int& targetYaw, int& targetDepth) {
    return new PowerTask(fpgaModel, powerOn, targetYaw, targetDepth);
}

MotorTask* TaskFactory::createMotorTask(Model* fpgaModel, bool powerOn, int& targetYaw, int& targetDepth) {
    return new MotorTask(fpgaModel, powerOn, targetYaw, targetDepth);
}

TaskFactory::~TaskFactory() {
    // TODO Auto-generated destructor stub
}
