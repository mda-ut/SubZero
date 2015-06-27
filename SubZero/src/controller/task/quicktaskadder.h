#ifndef QUICKTASKADDER_H
#define QUICKTASKADDER_H

#include "../../../git/SubZero/src/controller/controllers/Controller.h"
#include "../../../git/SubZero/src/controller/task/Task.h"
#include "../../../git/SubZero/src/controller/task/TaskCCR.h"
#include "../../../git/SubZero/src/controller/task/TaskHelloWorld.h"
#include "../../../git/SubZero/src/controller/task/TaskHeyTonight.h"
#include <QObject>


class QuickTaskAdder: public QObject
{
    Q_OBJECT
public:
    QuickTaskAdder();

public slots:
    void addTaskCCR();
    void addTaskHelloWorld();
    void addTaskHeyTonight();
    void initializeQuickTaskAdder(Controller *controllerOriginal);

private:

    Controller *controller;
};

#endif // QUICKTASKADDER_H
