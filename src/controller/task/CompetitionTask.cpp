#include "CompetitionTask.h"
#include "Controller.h"
#include <unistd.h>

CompetitionTask::CompetitionTask(PowerTask* powerTask, MotorTask* motorTask, GateTask *gateTask, PathTask *pathTask, BuoyTask* buoyTask) {
    this->powerTask = powerTask;
    this->motorTask = motorTask;
    this->gateTask = gateTask;
    this->pathTask = pathTask;
    this->buoyTask = buoyTask;
}

void CompetitionTask::execute() {
    PropertyReader* propReader;
    Properties* settings;
    propReader = new PropertyReader("../src/settings/competition_settings.txt");
    settings = propReader->load();

    logger->info("Starting competition run");
    // Give diver 15 seconds to aim SubZero towards gate
    powerTask->execute();
    usleep(15000000);
    motorTask->execute();
    usleep(5000000);
    gateTask->execute();
    if (settings->getProperty("RUN_PATH_TASK") == "true") {
        usleep(1000000);
        pathTask->execute();
    }
    if (settings->getProperty("RUN_BUOY_TASK") == "true") {
        usleep(1000000);
        buoyTask->execute();
    }
    if (settings->getProperty("RUN_PATH_TASK") == "true") {
        usleep(1000000);
        pathTask->execute();
    }
    if (settings->getProperty("RUN_PATH_TASK") == "true") {
        usleep(1000000);
        pathTask->execute();
    }
    if (settings->getProperty("RUN_PATH_TASK") == "true") {
        usleep(1000000);
        pathTask->execute();
    }
    powerTask->execute();
    logger->info("Competition run complete");
    Controller::running = false;
    usleep(3000000);
    exit(0);
}
