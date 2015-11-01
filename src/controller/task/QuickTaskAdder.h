#ifndef QUICKTASKADDER_H
#define QUICKTASKADDER_H

#include "../controller/controllers/Controller.h"
#include "../controller/task/Task.h"
#include <QObject>


class QuickTaskAdder: public QObject
{
    Q_OBJECT
public:
    QuickTaskAdder();

public slots:
    void initializeQuickTaskAdder(Controller *controllerOriginal);

private:

    Controller *controller;
};

#endif // QUICKTASKADDER_H
