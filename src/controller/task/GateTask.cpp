/*
 * GateTask.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: jwong
 */

#include "GateTask.h"
#include "Timer.h"

GateTask::GateTask() {
    // TODO Auto-generated constructor stub
}

GateTask::GateTask(Model* fpgaModel, DepthTask* depthTask, TurnTask* turnTask, SpeedTask* speedTask) {
    this->fpgaModel = fpgaModel;
    this->depthTask = depthTask;
    this->turnTask = turnTask;
    this->speedTask = speedTask;
}

void GateTask::execute() {
    // Load properties file
    PropertyReader* propReader;
    Properties* settings;
    propReader = new PropertyReader("../src/settings/gate_task_settings.txt");
    settings = propReader->load();

    logger->trace("Starting Gate Task");
    Timer timer;
    timer.start();
    FPGAData* temp = dynamic_cast<FPGAData*>(fpgaModel->getStateData("raw"));
    depthTask->setDepthAbsolute(temp->getDepth());
//    depthTask->setDepthAbsolute(std::stoi(settings->getProperty("POOL_SURFACE_HEIGHT")));
    depthTask->execute();
    logger->info("Set surface depth to " + std::to_string(temp->getDepth()));

    logger->info("Set starting yaw to " + std::to_string(temp->getYaw()));
    turnTask->setYawAbsolute(temp->getYaw());
    turnTask->execute();
    while (timer.getTimeElapsed() < 5) {
        std::this_thread::yield();
    }

    depthTask->setDepthDelta(std::stoi(settings->getProperty("START_DEPTH_DELTA")));    // Use relative depth movements
    depthTask->execute();\
    temp = dynamic_cast<FPGAData*>(fpgaModel->getStateData("raw"));
    logger->info("Sank to depth " + std::to_string(temp->getDepth()));
    timer.start();
    while (timer.getTimeElapsed() < std::stoi(settings->getProperty("DEPTH_WAIT_TIME"))) {
        std::this_thread::yield();
    }

    // Move straight forward
    speedTask->setTargetSpeed(std::stoi(settings->getProperty("FORWARD_SPEED")));
    speedTask->execute();
    logger->info("Moving forward at speed " + std::stoi(settings->getProperty("FORWARD_SPEED")));
    timer.start();
    while (timer.getTimeElapsed() < std::stoi(settings->getProperty("FORWARD_TIME"))) {
        std::this_thread::yield();
    }

    // Try to decelerate
    speedTask->setTargetSpeed(std::stoi(settings->getProperty("REVERSE_SPEED")));
    speedTask->execute();
    logger->info("Moving forward at speed " + std::stoi(settings->getProperty("REVERSE_SPEED")));
    timer.start();
    while (timer.getTimeElapsed() < std::stoi(settings->getProperty("REVERSE_TIME"))) {
        std::this_thread::yield();
    }

    // Stop
    logger->info("Stopping");
    speedTask->setTargetSpeed(0);
    speedTask->execute();

    depthTask->setDepthDelta(100);
    depthTask->execute();

    logger->info("Gate Task complete");
}

GateTask::~GateTask() {
    delete logger;
}

