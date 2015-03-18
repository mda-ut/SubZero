/* menu Class header
February 7 2015 */

#ifndef MENU_H_
#define MENU_H_


#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
/**
 * This class manages all views. It is capable of
 * instantiating and terminating views, as well as
 * switching between active views  using the signals
 * and slots inherit to the Qt Classes within itself
 */


class Menu {

	Q_OBJECT

public:
  Menu();
  virtual ~Menu();

  QWidget menuWIndow;
  QComboBox viewSelecter;
  QPushButton affirmSele;
  QComboBox viewTerminator;
  QPushButton affirmTerm;
  QGridLayout menuLayout;
  QLabel currentView;

};

#endif
