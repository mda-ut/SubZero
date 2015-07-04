#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QFont>
#include <QMouseEvent>
#include <QPoint>
#include <QObject>
#include "PropertyReader.h"



class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu(PropertyReader* settings_);
    virtual ~Menu();
    void paintEvent(QPaintEvent *event);


    QSize buttonRectSize;
    QFont menuItemFont;
    QPoint temp;
    QFont welcomeFont;

    QLabel *welcomeMessage;
    QPushButton *guiButton;
    QPushButton *simButton;
    QPushButton *autButton;

    QGridLayout *mainLayout;

    PropertyReader* settings;

private:
    void initializeMenu();


public slots:
   void makeGuiView();
  /*
  void makeGuiView();
  void makeSimView();
  void makeAutView();
  */
};

#endif // MENU_H
