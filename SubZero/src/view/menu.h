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



class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu();
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

private:
    void initializeMenu();


public slots:
   void makeView();
  /*
  void makeGuiView();
  void makeSimView();
  void makeAutView();
  */
};

#endif // MENU_H
