/*
 * Controller.cpp
 *
 *  Created on: Mar 12, 2015
 *      Author: ed
 */

#include "Controller.h"
#include "ControllerThread.h"
#include "GUIView.h"
#include "MenuView.h"
#include <iostream>

bool Controller::running = false;

Controller::Controller() {
    taskList = new QQueue <class Task* >;
}

Controller::Controller(std::vector<Model*> models){
    this->models = models;
    targetDepth = 300;
    targetYaw = 0;
    taskList = new QQueue <class Task* >;
}

void Controller::initialize(void) {
    logger->info("Initializing Controller");
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
Controller::~Controller() {
    stop();
    delete taskList;
    delete logger;
}

bool Controller::isRunning() {
    return running;
}

void Controller::setView(View *view) {
    this->view = view;
}

void Controller::finished(const QString &s){
    logger->info("Controller Thread finished");
}

static bool powerStatus = false;
void Controller::handlePowerButtonToggled() {

    logger->info("Adding Power Task to queue");
    powerStatus = !powerStatus;
    addTaskToQueue(TaskFactory::createPowerTask(models[FPGA]));
}

void Controller::handleMotorButtonClick() {
    logger->info("Adding Motor Task to queue");
    addTaskToQueue(TaskFactory::createMotorTask(models[FPGA]));
}

void Controller::handleMoveLeftButtonClick() {
    logger->info("Adding Move Left Task to queue");
    addTaskToQueue(TaskFactory::createTurnTask(models[FPGA], targetYaw, -15));
}

void Controller::handleMoveRightButtonClick() {
    logger->info("Adding Move Right Task to queue");
    addTaskToQueue(TaskFactory::createTurnTask(models[FPGA], targetYaw, 15));
}

void Controller::handleMoveForwardButtonClick() {
    logger->info("Adding Move Forward Task to queue");
    addTaskToQueue(TaskFactory::createSpeedTask(models[FPGA], 18*6));
}

void Controller::handleMoveBackwardButtonClick() {
    logger->info("Adding Move Backward Task to queue");
    addTaskToQueue(TaskFactory::createSpeedTask(models[FPGA], -18*6));
}

void Controller::handleStopButtonClick() {
    logger->info("Adding Stop Task to queue");
    addTaskToQueue(TaskFactory::createSpeedTask(models[FPGA], 0));
}

void Controller::handleSinkButtonClick() {
    logger->info("Adding Sink Task to queue");
    addTaskToQueue(TaskFactory::createDepthTask(models[FPGA], targetDepth, 50));
}

void Controller::handleRiseButtonClick() {
    logger->info("Adding Rise Task to queue");
    addTaskToQueue(TaskFactory::createDepthTask(models[FPGA], targetDepth, -50));
}

void Controller::handleGateTaskClick() {
    logger->info("Adding Gate Task to queue");
    addTaskToQueue(TaskFactory::createGateTask(models[FPGA], targetDepth, targetYaw));
}

void Controller::handlePathTaskClick() {
    logger->info("Adding Path Task to queue");
    addTaskToQueue(TaskFactory::createPathTask(models[DOWNCAM], models[FPGA], targetYaw));
}

void Controller::runCompetition() {
    logger->info("Adding Competition Task to queue");
    addTaskToQueue(TaskFactory::createCompetitionTask(models[FRONTCAM], models[DOWNCAM], models[FPGA], targetDepth, targetYaw));
}

void Controller::stop() {
    running = false;
    if(queueThread.isRunning()) {
        queueThread.quit();
        queueThread.wait();
    }
    while(!taskList->isEmpty()) {
        Task *temp = taskList->dequeue();
        delete temp;
    }
}


void Controller::addTaskToQueue(Task *newTask)
{
    logger->trace("Requesting mutex lock to add task");
    mutex.lock();
    logger->trace("Lock request successful");
    taskList->enqueue(newTask);
    logger->trace("Enqueued new task");
    mutex.unlock();
    logger->trace("Unlocking mutex");

}
