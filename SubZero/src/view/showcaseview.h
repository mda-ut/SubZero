#ifndef SHOWCASEVIEW_H
#define SHOWCASEVIEW_H

#include "view.h"
#include <QPushButton>
#include <QLabel>
#include "../controller/controllers/Controller.h"
#include "quicktaskadder.h"

//#include <QAction> // for actions later on (systemActions)


class ShowCaseView : public View
{
public:
    ShowCaseView();

    QLabel* movement;
    QPushButton *leftButton;
    QPushButton *rightButton;

    QLabel* specialActions;
    QPushButton *surfaceButton;
    QPushButton *fireTorpedoButton;
    QPushButton *fireGrabberButton;

    QLabel* systemActions;
    QPushButton *menuButton;
    QPushButton *exitButton;

    void initialize_VC_Connection(Controller *controller);



private:
    void initializeShowCaseView();
    void makeQImage(Mat* imgData, QImage *imgHolder);



};

#endif // SHOWCASEVIEW_H
