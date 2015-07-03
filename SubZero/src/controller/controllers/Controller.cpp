/*
 * Controller.cpp
 *
 *  Created on: Mar 12, 2015
 *      Author: ed
 */

#include "Controller.h"
#include "ControllerThread.h"
#include <iostream>

bool Controller::running = false;

Controller::Controller(){
    taskList = new QQueue <class Task* >;
}

Controller::Controller(std::vector<Model*> models_){
    models = models_;
    taskList = new QQueue <class Task* >;
}

void Controller::initialize(void) {
    cT = new ControllerThread(taskList, &mutex);
    cT->moveToThread(&queueThread);
    connect(this, &Controller::beginCT, cT, &ControllerThread::executeTasks);
    connect(cT, &ControllerThread::resultReady, this, &Controller::finished);
    connect(&queueThread, &QThread::finished, cT, &QObject::deleteLater);
    queueThread.start();
    running = true;
    emit beginCT("Begin handling Commands");
}

    //Destructor to free pointers
Controller::~Controller(){
    if(queueThread.isRunning()){
        queueThread.quit();
        queueThread.wait();
    }
    while(!taskList->isEmpty()){
        Task *temp = taskList->dequeue();
        delete temp;
    }
    delete taskList;
}

bool Controller::isRunning() {
    return running;
}

void Controller::finished(const QString &s){
    std::cout << "Bye Bye Beautiful!!" << std::endl;
}

void Controller::handleMoveLeftButtonClick() {
    logger->info("Adding Move Left Task to queue");
    addTaskToQueue(TaskFactory::createMoveLeftTask(models));
}

void Controller::handleMoveRightButtonClick() {
    logger->info("Adding Move Right Task to queue");
    addTaskToQueue(TaskFactory::createMoveLeftTask(models));
}

void Controller::handleMoveForwardButtonClick() {
    logger->info("Adding Move Forward Task to queue");
    addTaskToQueue(TaskFactory::createMoveLeftTask(models));
}

void Controller::handleMoveBackwardButtonClick() {
    logger->info("Adding Move Backward Task to queue");
    addTaskToQueue(TaskFactory::createMoveLeftTask(models));
}

void Controller::handleSinkButtonClick() {
    logger->info("Adding Sink Task to queue");
    addTaskToQueue(TaskFactory::createMoveLeftTask(models));
}

void Controller::handleRiseButtonClick() {
    logger->info("Adding Rise Task to queue");
    addTaskToQueue(TaskFactory::createMoveLeftTask(models));
}

void Controller::killAll() {
    logger->info("Exiting...");
    running = false;
}


void Controller::addTaskToQueue(Task *newTask)
{
    mutex.lock();
    taskList->enqueue(newTask);
    mutex.unlock();
}
