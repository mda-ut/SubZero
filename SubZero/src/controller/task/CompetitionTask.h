#ifndef COMPETITIONTASK_H
#define COMPETITIONTASK_H
#include "Task.h"
#include "PowerTask.h"
#include "MotorTask.h"
#include "GateTask.h"
#include "PathTask.h"
#include "BuoyTask.h"
#include "Logger.h"

class CompetitionTask: public Task
{
public:
    CompetitionTask(PowerTask* powerTask, MotorTask* motorTask, GateTask* gateTask, PathTask* pathTask, BuoyTask* buoyTask);

    void execute();
private:
    Logger* logger = new Logger("CompetitionTask");
    PowerTask* powerTask;
    MotorTask* motorTask;
    GateTask* gateTask;
    PathTask* pathTask;
    BuoyTask* buoyTask;
    Properties* settings;

};

#endif // COMPETITIONTASK_H
