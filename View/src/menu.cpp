#include "menu.h"
#include <QDebug>
#include <guiview.h>

Menu::Menu(QWidget *parent) :
    QWidget(parent)
{
    /** @param Selector This item holds all views.
     * It shall be replaced in the future probably
     * with list widget or tree widget.
     *
     * @param affirmButton This button is used to
     * confirm the desired instantiation of a view.
     */

    selector = new QComboBox;
    affirmButton = new QPushButton;
    horizontal1 = new QHBoxLayout;

    //Initializing the layout
    selector->addItem("GUI");
    selector->addItem("SIM");

    affirmButton->setText("Ok");

    horizontal1->addWidget(selector);
    horizontal1->addWidget(affirmButton);

    this->setLayout(horizontal1);

    //Connecting Signals and Slots
    connect(affirmButton, SIGNAL(clicked()),SLOT(makeView()));

}

/**
 * @param makeView Instantiates the current selected view
 */

void Menu::makeView()
{
    if (selector->currentText() == "GUI")
    {
        qDebug()<< "Initiating GUI";

       GuiView *GUI = new GuiView;
       GUI->show();
       this->close();


    }
    else if (selector->currentText() == "SIM")
    {
       qDebug()<< "Initiating Simulation mode";
    }
}
