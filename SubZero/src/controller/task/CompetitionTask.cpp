#include "CompetitionTask.h"
#include <unistd.h>

CompetitionTask::CompetitionTask(GateTask *gateTask, PathTask *pathTask) {
    this->gateTask = gateTask;
    this->pathTask = pathTask;
}

void CompetitionTask::execute() {
    logger->info("Starting competition run");
    // Give diver 15 seconds to aim SubZero towards gate
    usleep(15000000);
    gateTask->execute();
    usleep(1000000);
    pathTask->execute();
    logger->info("Competition run complete");
}
