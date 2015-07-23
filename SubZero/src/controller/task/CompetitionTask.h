#ifndef COMPETITIONTASK_H
#define COMPETITIONTASK_H
#include "Task.h"
#include "GateTask.h"
#include "PathTask.h"
#include "Logger.h"

class CompetitionTask: public Task
{
public:
    CompetitionTask(GateTask* gateTask, PathTask* pathTask);

    void execute();
private:
    Logger* logger = new Logger("CompetitionTask");

    GateTask* gateTask;
    PathTask* pathTask;
    Properties* settings;

};

#endif // COMPETITIONTASK_H
