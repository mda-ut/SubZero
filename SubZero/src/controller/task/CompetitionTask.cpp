#include "CompetitionTask.h"
#include "Controller.h"
#include <unistd.h>

CompetitionTask::CompetitionTask(PowerTask* powerTask, MotorTask* motorTask, GateTask *gateTask, PathTask *pathTask) {
    this->powerTask = powerTask;
    this->motorTask = motorTask;
    this->gateTask = gateTask;
    this->pathTask = pathTask;
}

void CompetitionTask::execute() {
    logger->info("Starting competition run");
    // Give diver 15 seconds to aim SubZero towards gate
    powerTask->execute();
    usleep(15000000);
    usleep(3000000);
    motorTask->execute();
    usleep(5000000);
    gateTask->execute();
    //    usleep(1000000);
    //    pathTask->execute();

    powerTask->execute();
    logger->info("Competition run complete");
    Controller::running = false;
    usleep(3000000);
    exit(0);
}
