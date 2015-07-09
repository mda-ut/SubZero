#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QPaintEvent>
//#include "observer.h"    //Need a concrete observer class
#include <vector>

class State;
class Controller;

class View : public QWidget {

    Q_OBJECT

public:
    View();
    View(std::vector<State*> states_);
    virtual ~View();

    virtual void update(int ID) = 0;
    virtual void initialize() = 0;

protected:
    std::vector<State*> states;

    void paintEvent(QPaintEvent *event); // All drawing and painting will take place in here

};

#endif // VIEW_H
