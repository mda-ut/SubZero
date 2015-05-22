#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QFont>
#include <QMouseEvent>
#include <QPoint>

class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu();
    void paintEvent(QPaintEvent *event);


private:
    QSize buttonRectSize;
    QFont menuItemFont;
    QPoint temp;
    QFont welcomeFont;

    QLabel *welcomeMessage;
    QPushButton *guiButton;
    QPushButton *simButton;
    QPushButton *autButton;

    QGridLayout *mainLayout;



public slots:
  void makeGuiView();
  void makeSimView();
  void makeAutView();
};

#endif // MENU_H

