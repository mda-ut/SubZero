#include "showcaseview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QBrush>
#include <QLinearGradient>
#include <QSignalMapper>

#include "../../../git/SubZero/src/controller/task/Task.h"
#include "../../../git/SubZero/src/controller/task/TaskCCR.h"
#include "../../../git/SubZero/src/controller/task/TaskHelloWorld.h"
#include "../../../git/SubZero/src/controller/task/TaskHeyTonight.h"


ShowCaseView::ShowCaseView():View()
{
    initializeShowCaseView();

}

void ShowCaseView::initializeShowCaseView()
{
    *frontCameraImage = QImage(":/img/MDA.jpg");



   //Creating an image that holds a gradient of blue

        //Create an image to be painted on
   QImage sub(400,500,QImage::Format_RGB32);

        //Setup the painter to paint/draw on the image
   QPainter subImgPainter;
   subImgPainter.begin(&sub); //Paint on that image

        //Create the gradient
   QLinearGradient blueGradient(0,0,800,600);

        //Set the starting color and end colors
   blueGradient.setColorAt(0.0,QColor(62,58,200));// 0.0 is start position as a qreal
   blueGradient.setColorAt(1.0,QColor(175,80,255)); //1.0 is end position as a qreal

        //Create a brush from the gradient (to paint with)
   QBrush blueGradientBrush(blueGradient);

        //Use the brush
   subImgPainter.fillRect(sub.rect(), blueGradientBrush);
   subImgPainter.end();



    *downCameraImage = sub;







    // Show Case View WIdget Initialization
    movement = new QLabel("Movement");
    leftButton = new QPushButton("Veer Left");
    rightButton = new QPushButton("Veer right");

    specialActions = new QLabel("Special Actions");
    surfaceButton = new QPushButton("Surface");
    fireTorpedoButton = new QPushButton("Fire Torpedo");
    fireGrabberButton = new QPushButton("Fire Grabber");

    systemActions = new QLabel("System Actions");
    menuButton = new QPushButton("Menu");
    exitButton = new QPushButton("Exit");


    // Show Case View layouts

    QVBoxLayout *verticalLayout = new QVBoxLayout;
    QHBoxLayout *mainLayout = new QHBoxLayout;

    //Show Case view Widget Positioning
    //Down want to add rects from view to layout
    //What to do? : set other BoxLayouts and add spacing?

    verticalLayout->addWidget(movement);
    verticalLayout->addWidget(leftButton);
    verticalLayout->addWidget(rightButton);
    verticalLayout->addSpacing(20);//Spacing size of 20 pixels

    verticalLayout->addWidget(specialActions);
    verticalLayout->addWidget(surfaceButton);
    verticalLayout->addWidget(fireTorpedoButton);
    verticalLayout->addWidget(fireGrabberButton);
    verticalLayout->addSpacing(20);//Spacing size of 20 pixels

    verticalLayout->addWidget(systemActions);
    verticalLayout->addWidget(menuButton);
    verticalLayout->addWidget(exitButton);
    verticalLayout->addSpacing(200);//Spacing size of 200 pixels

    mainLayout->addSpacing(800);
    mainLayout->addLayout(verticalLayout);
    this->setLayout(mainLayout);



}


void ShowCaseView::makeQImage(cv::Mat *imgData, QImage *imgHolder)
{
    *imgHolder = QImage(imgData->data, imgData->cols, imgData->rows,QImage::Format_RGB32);

    return;
}



void ShowCaseView::initialize_VC_Connection(Controller *controller)
{
    //Test code to check view and controller connection capabilities
    //Links the 1st 3 buttons of view to controller's first tasks. TaskCCR, TaskHeyTonight, TaskHelloWorld

    //Create holder functions since having trouble with task* - QObject * conversions

    QuickTaskAdder *qta = new QuickTaskAdder();
    qta->initializeQuickTaskAdder(controller);

    connect(leftButton, SIGNAL(clicked()), qta, SLOT(addTaskCCR()));


}

