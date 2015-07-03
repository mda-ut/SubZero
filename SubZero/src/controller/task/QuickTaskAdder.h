#ifndef QUICKTASKADDER_H
#define QUICKTASKADDER_H

#include "../controller/controllers/Controller.h"
#include "../controller/task/Task.h"
#include "../controller/task/TaskCCR.h"
#include "../controller/task/TaskHelloWorld.h"
#include "../controller/task/TaskHeyTonight.h"
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
