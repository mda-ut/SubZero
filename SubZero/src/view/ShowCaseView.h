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
    virtual ~ShowCaseView();

    QLabel* powerStatus;
    QPushButton *powerButton;
    QPushButton *motorButton;

    QLabel* movement;
    QPushButton *leftButton;
    QPushButton *rightButton;

    QPushButton *forwardButton;
    QPushButton *backwardButton;
    QPushButton *sinkButton;
    QPushButton *riseButton;
    QPushButton *stopButton;

    QLabel* specialActions;
    QPushButton *surfaceButton;
    QPushButton *gateButton;
    QPushButton *pathButton;

    QLabel* systemActions;
    QPushButton *menuButton;
    QPushButton *exitButton;

    QLabel* depthReading;
    QLabel* yawReading;

    QLabel* targetDepthLabel;
    QLabel* targetYawLabel;

    virtual void update(int ID);
    void initialize_VC_Connection(Controller *controller);

private:
    Logger* logger = new Logger("ShowCaseView");

    virtual void initializeShowCaseView();

};

#endif // SHOWCASEVIEW_H
