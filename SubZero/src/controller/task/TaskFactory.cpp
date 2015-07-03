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

MoveLeftTask* TaskFactory::createMoveLeftTask(std::vector<Model*> models) {
    return new MoveLeftTask(models);
}

TaskFactory::~TaskFactory() {
    // TODO Auto-generated destructor stub
}
