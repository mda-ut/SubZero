#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QPaintEvent>
#include <vector>
#include "State.h"
#include "Controller.h"

class Stage;

class View : public QWidget {

    Q_OBJECT

public:
    View();
    View(Stage* stage, Controller* controller, std::vector<State*> states);
    virtual ~View();

    virtual void update(int ID) = 0;
    virtual void initialize() = 0;

protected:
    Stage* stage;
    Controller* controller;
    std::vector<State*> states;
};

#endif // VIEW_H
