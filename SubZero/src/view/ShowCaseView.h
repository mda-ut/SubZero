#ifndef SHOWCASEVIEW_H
#define SHOWCASEVIEW_H

#include "View.h"
#include <QPushButton>
#include <QLabel>
#include "../controller/controllers/Controller.h"
#include "QuickTaskAdder.h"

//#include <QAction> // for actions later on (systemActions)


class ShowCaseView : public View
{
public:
    ShowCaseView();
    ShowCaseView(std::vector<State*> states_);

    QPushButton *powerButton;

    QLabel* movement;
    QPushButton *leftButton;
    QPushButton *rightButton;

    QPushButton *forwardButton;
    QPushButton *backwardButton;
    QPushButton *sinkButton;
    QPushButton *riseButton;

    QLabel* specialActions;
    QPushButton *surfaceButton;
    QPushButton *fireTorpedoButton;
    QPushButton *fireGrabberButton;

    QLabel* systemActions;
    QPushButton *menuButton;
    QPushButton *exitButton;

    QLabel* depthReading;
    QLabel* yawReading;

    virtual void update(int ID);
    void initialize_VC_Connection(Controller *controller);


private:
    virtual void initializeShowCaseView();

};

#endif // SHOWCASEVIEW_H
