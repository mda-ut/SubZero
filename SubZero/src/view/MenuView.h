#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QPaintEvent>
#include <QSize>
#include <cv.h>
#include <highgui.h>

#include "Logger.h"
#include "Properties.h"
#include "View.h"

class MenuView : public View {

public:
    MenuView();
    MenuView(Stage* stage);
    ~MenuView();

    virtual void initialize();
    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;

public slots:
    virtual void update(int id);


protected:
    void paintEvent(QPaintEvent* event);

private:
    Logger* logger = new Logger("MenuView");

    QSize buttonSize;
    QFont menuItemFont;
    QFont welcomeFont;

    QLabel *welcomeMessage;
    QPushButton *guiButton;
    QPushButton *simulatorButton;
    QPushButton *autonomousButton;

    QGridLayout *menuLayout;

    Properties* settings;

};

#endif // MENUVIEW_H
