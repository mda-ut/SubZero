#include "MenuView.h"

#include <QDebug>
#include <QString>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QColor>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Stage.h"

MenuView::MenuView() {

}

MenuView::MenuView(Stage* stage) : View() {
    this->stage = stage;
}

void MenuView::update(int id) {
    // Nothing to do in this View
}

void MenuView::initialize() {
    buttonSize = QSize(150,50);
    setWindowTitle("Sub Menu");
    this->setFixedSize(800,600);

    //Welcome
    welcomeMessage = new QLabel();

    //Sizing private:
    welcomeMessage->setFixedSize(400,300);

    //Font
    welcomeFont = QFont("Calibri",15);
    welcomeFont.setItalic(true);
    welcomeFont.setBold(true);

    //Set Text
    welcomeMessage->setFont(welcomeFont);
    welcomeMessage->setText("Welcome to the menu\nPlease make a selection");

    //Making the Buttons
    guiButton = new QPushButton();
    simulatorButton = new QPushButton();
    autonomousButton = new QPushButton();

    //Sizing
    guiButton->setFixedSize(buttonSize);
    simulatorButton->setFixedSize(buttonSize);
    autonomousButton->setFixedSize(buttonSize);

    //Text Sizing and Font
    menuItemFont = QFont("Times New Roman",12);
    menuItemFont.setItalic(true);

    guiButton->setFont(menuItemFont);
    simulatorButton->setFont(menuItemFont);
    autonomousButton->setFont(menuItemFont);

    //Change Color when mouse hovers over a menu setMouseTrack item
    guiButton->setStyleSheet("QPushButton:hover{ background-color : lightGrey; color:black}");
    simulatorButton->setStyleSheet("QPushButton:hover{ background-color : lightGrey; color:black}");
    autonomousButton->setStyleSheet("QPushButton:hover{ background-color : lightGrey; color:black}");

    //Text
    guiButton->setText("Gui Mode");
    simulatorButton->setText("Simulation Mode");
    autonomousButton->setText("Autonomous Mode");

    // Layout
    menuLayout = new QGridLayout(this);
    menuLayout->setSpacing(10);

    for (int i = 0; i<10; i++) {
        //Setting max size relative to minimum for the first 10 rows
        menuLayout->setRowStretch(i,1);
    }

    for (int i = 0; i<10; i++) {
        //Setting 10 rows of equal "size" 100
        menuLayout->setRowMinimumHeight(i,100);
    }

    for (int i = 0; i<10; i++) {
        //Setting max size relative to minimum for the first 10 Columns
        menuLayout->setColumnStretch(i,1);
    }

    for (int i = 0; i<10; i++) {
        //Setting 10 Columns of equal "size" 100
        menuLayout->setColumnMinimumWidth(i,100);
    }

    //Positioning      *note that the widgets span multiple rows and columns
    menuLayout->addWidget(welcomeMessage,0,5);
    menuLayout->addWidget(guiButton,4,6);
    menuLayout->addWidget(simulatorButton,5,6);
    menuLayout->addWidget(autonomousButton,6,6);
    this->setLayout(menuLayout);

    //Leave only the button text visible
    guiButton->setFlat(true);
    simulatorButton->setFlat(true);
    autonomousButton->setFlat(true);

    connect(guiButton, SIGNAL(clicked()), stage, SLOT(switchToGUIView()));

}

QSize MenuView::sizeHint() const {
    return QSize(800,600);
}

QSize MenuView::minimumSizeHint() const {
    return QSize(800,600);
}

void MenuView::paintEvent(QPaintEvent *event) {

    QImage background(":/img/MDA.jpg");
    background = background.scaled(800,700);

    QPainter painter;

    painter.begin(this);
    painter.fillRect(event->rect(), background);

    painter.end();
}

MenuView::~MenuView() {
    delete logger;
}



