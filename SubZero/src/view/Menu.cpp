#include "Menu.h"
#include <QDebug>
#include <QString>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QColor>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>


#include "ShowCaseView.h"

//#include "guiview.h"
//#include "simview.h"
//#include "autview.h"
#include "SubZeroFactory.h"
/**
 * Menu for insantiating views
 */


Menu::Menu(Properties* settings_)
{
    settings = settings_;
    initializeMenu();
}


void Menu::initializeMenu()
{
    // setMouseTracking(true);
     buttonRectSize = QSize(150,50);
     setWindowTitle("Sub Menu");
     this->setFixedSize(800,600);

     //Welcome
     welcomeMessage = new QLabel();

         //Sizingprivate:
     welcomeMessage->setFixedSize(400,300);

         //Font
     welcomeFont = QFont("Calibri",15);
     welcomeFont.setItalic(true);
     welcomeFont.setBold(true);

         //Set Text
     welcomeMessage->setFont(welcomeFont);
     welcomeMessage->setText("Welcome to the menu\nPlease select your view");



     //Making the Buttons
     guiButton = new QPushButton();
     simButton = new QPushButton();
     autButton = new QPushButton();


          //Connecting
     connect(guiButton, SIGNAL(clicked()), this, SLOT(makeGuiView()));


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

        //Change Color when mouse hovers over a menu setMouseTrack item
     guiButton->setStyleSheet("QPushButton:hover{ background-color : lightGrey; color:black}");
     simButton->setStyleSheet("QPushButton:hover{ background-color : lightGrey; color:black}");
     autButton->setStyleSheet("QPushButton:hover{ background-color : lightGrey; color:black}");


         //Text
     guiButton->setText("Gui Mode");
     simButton->setText("Simulation Mode");
     autButton->setText("Autonomous Mode");



     //Layout

         //Sizing
     mainLayout = new QGridLayout();

     mainLayout->setSpacing(10);

     for (int i = 0; i<10; i++)
    {
         mainLayout->setRowStretch(i,1); //Setting max size relative to minimum for the first 10 rows
    }

     for (int i = 0; i<10; i++)
    {
     mainLayout->setRowMinimumHeight(i,100); //Setting 10 rows of equal "size" 100
     }


     for (int i = 0; i<10; i++)
    {
         mainLayout->setColumnStretch(i,1); //Setting max size relative to minimum for the first 10 Columns
    }

     for (int i = 0; i<10; i++)
    {
        mainLayout->setColumnMinimumWidth(i,100); //Setting 10 Columns of equal "size" 100
    }

         //Positioning      *note that the widgets span multiple rows and columns
     mainLayout->addWidget(welcomeMessage,0,5);
     mainLayout->addWidget(guiButton,4,6);
     mainLayout->addWidget(simButton,5,6);
     mainLayout->addWidget(autButton,6,6);
     this->setLayout(mainLayout);


     //Leave only the button text visible

     guiButton->setFlat(true);
     simButton->setFlat(true);
     autButton->setFlat(true);

}

Menu::~Menu(){
    delete settings;
}


void Menu::paintEvent(QPaintEvent *event)
{

     QImage background(":/img/MDA.jpg");
     background = background.scaled(800,700);

    QPainter painter;

     painter.begin(this);
    painter.fillRect(event->rect(), background);

    painter.end();
}


void Menu::makeGuiView()
{
    /*ShowCaseView *view = new ShowCaseView;
    view->show();

    Controller* controller = new Controller;
    controller->initialize();
*/
    SubZeroFactory subFactory;
    SubZero* guiSub = subFactory.makeSubZero(GUI, settings);
    guiSub->init();
    this->close();
    guiSub->run();
    delete guiSub;
}
