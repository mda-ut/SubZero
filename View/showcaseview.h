#ifndef SHOWCASEVIEW_H
#define SHOWCASEVIEW_H

#include "view.h"
#include <QPushButton>
#include <QLabel>


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





private:
    void initializeShowCaseView();
    void makeQImage(Mat* imgData, QImage *imgHolder);
   // void initialize_VC_Connection(ShowCaseView::controller *controller);


};

#endif // SHOWCASEVIEW_H
