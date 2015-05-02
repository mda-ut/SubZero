/* menu Class header
February 7 2015 */
#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = 0);
    QComboBox *selector;
    QPushButton *affirmButton;
    QHBoxLayout *horizontal1;

//signals:

public slots:
    void makeView();


};

#endif // MENU_H
