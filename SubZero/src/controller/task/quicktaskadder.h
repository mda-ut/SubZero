#ifndef QUICKTASKADDER_H
#define QUICKTASKADDER_H

#include "../controllers/Controller.h"
#include "Task.h"
#include "TaskCCR.h"
#include "TaskHelloWorld.h"
#include "TaskHeyTonight.h"
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
