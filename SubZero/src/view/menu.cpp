#include "menu.h"
#include <QDebug>
#include <QString>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QColor>
#include <QWidget>

#include "guiview.h"
#include "simview.h"
#include "autview.h"

/**
 * Menu for insantiating views
 */


Menu::Menu()
{
    setMouseTracking(true);
    buttonRectSize = QSize(150,50);
    setWindowTitle("Sub Menu");
    this->setFixedSize(800,600);

    //Welcome
    welcomeMessage = new QLabel();

        //Sizing
    welcomeMessage->setFixedSize(400,300);

        //Font
    welcomeFont = QFont("Calibri",15);
    welcomeFont.setItalic(true);
    welcomeFont.setBold(true);

        //Set Text
    welcomeMessage->setFont(welcomeFont);
    welcomeMessage->setText("Welcome to the menu\nPlease select your view");




    //Making the Buttons
    guiButton = new QPushButton(this);
    simButton = new QPushButton(this);
    autButton = new QPushButton(this);

    connect(guiButton, SIGNAL(clicked()), this, SLOT(makeView()));


         //Sizing
    guiButton->setFixedSize(buttonRectSize);
    simButton->setFixedSize(buttonRectSize);
    autButton->setFixedSize(buttonRectSize);

        //Text Sizing and Font
    menuItemFont = QFont("Times New Roman",12);
    menuItemFont.setItalic(true);

    guiButton->setFont(menuItemFont);
    simButton->setFont(menuItemFont);
    autButton->setFont(menuItemFont);


        //color
    guiButton->setStyleSheet("QPushButton{ background-color : yellow; color:blue}");
    simButton->setStyleSheet("QPushButton{ background-color : yellow; color:blue}");
    autButton->setStyleSheet("QPushButton{ background-color : yellow; color:blue}");


        //Change Color when mouse hovers over a menu item
    guiButton->setStyleSheet("QPushButton:hover{ background-color : lightGrey; color:black}");
    simButton->setStyleSheet("QPushButton:hover{ background-color : lightGrey; color:black}");
    autButton->setStyleSheet("QPushButton:hover{ background-color : lightGrey; color:black}");

    //Consider using setBackGroundImage to achieve a nicer effect


        //Text
    guiButton->setText("Gui Mode");
    simButton->setText("Simulation Mode");
    autButton->setText("Autonomous Mode");



    //Layout
    mainLayout = new QGridLayout();

    mainLayout->setSpacing(10);
    mainLayout->addWidget(welcomeMessage,1,3);
    mainLayout->addWidget(guiButton,2,4);
    mainLayout->addWidget(simButton,3,4);
    mainLayout->addWidget(autButton,4,4);
    this->setLayout(mainLayout);


    //Leave only the button text visible

    guiButton->setFlat(true);
    simButton->setFlat(true);
    autButton->setFlat(true);



}





void Menu::paintEvent(QPaintEvent *event)
{
 QBrush background(QColor(32,32,32,0));//Grey brush to paint background with
 QPainter painter;

 painter.begin(this);
 painter.fillRect(event->rect(), background);

 painter.end();
}

void Menu::makeGuiView()
{
    GuiView *guiView = new GuiView;
   
}
/*Not made yet
 *
 *
void Menu::makeSimView()
{
    SimView *simView = new SimView;
    delete this;
}

void Menu::makeAutView()
{
    AutView *autView = new autView;
    delete this;
}

*/
