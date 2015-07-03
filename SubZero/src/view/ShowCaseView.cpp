#include "ShowCaseView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QBrush>
#include <QLinearGradient>
#include <QSignalMapper>

#include "../controller/task/Task.h"
#include "../controller/task/TaskCCR.h"
#include "../controller/task/TaskHelloWorld.h"
#include "../controller/task/TaskHeyTonight.h"


ShowCaseView::ShowCaseView():View() {
    initializeShowCaseView();
}

ShowCaseView::ShowCaseView(std::vector<State *> states_) : View(states_) {
    initializeShowCaseView();
}

void ShowCaseView::update(int ID) {
    // Update Cameras
    switch (ID) {
    case FRONTCAM: {
        ImgData* newImg = dynamic_cast<ImgData*>(states[0]->getState("raw"));
        makeQImage(newImg->img, frontCameraImage);
        //std::cout << "make front" << std::endl;
        break;
    }
    case DOWNCAM: {
        ImgData* newImg = dynamic_cast<ImgData*>(states[1]->getState("raw"));
        makeQImage(newImg->img, downCameraImage);
        //std::cout << "make down" << std::endl;
        break;
    }
    case FPGA: {
        // Update Depth and Yaw readings
        FPGAData* newData = dynamic_cast<FPGAData*>(states[2]->getState("raw"));
        double depth = newData->getDepth();
        double yaw = newData->getHeading();
        double speed = newData->getSpeed();
        std::string temp = "Depth: " + std::to_string(depth);
        depthReading->setText(temp.c_str());
        temp = "Yaw: " + std::to_string(yaw);
        yawReading->setText(temp.c_str());
        temp = "Accel x: " + std::to_string(speed);
        accelReading->setText(temp.c_str());
        break;
    }
    }
    repaint();
}

void ShowCaseView::initializeShowCaseView() {
    frontCameraImage = QImage(":/img/MDA.jpg");

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



    downCameraImage = sub;


    // Show Case View WIdget Initialization
    movement = new QLabel("Movement");
    leftButton = new QPushButton("Veer Left");
    rightButton = new QPushButton("Veer right");

    forwardButton = new QPushButton("Move Forward");
    backwardButton = new QPushButton("Move Backward");
    sinkButton = new QPushButton("Sink");
    riseButton = new QPushButton("Rise");

    specialActions = new QLabel("Special Actions");
    surfaceButton = new QPushButton("Surface");
    fireTorpedoButton = new QPushButton("Fire Torpedo");
    fireGrabberButton = new QPushButton("Fire Grabber");

    systemActions = new QLabel("System Actions");
    menuButton = new QPushButton("Menu");
    exitButton = new QPushButton("Exit");

    depthReading = new QLabel("Depth:");
    yawReading = new QLabel("Yaw:");
    accelReading = new QLabel("Accel: ");

    // Show Case View layouts

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QHBoxLayout *mainLayout = new QHBoxLayout();

    //Show Case view Widget Positioning
    //Down want to add rects from view to layout
    //What to do? : set other BoxLayouts and add spacing?

    verticalLayout->addWidget(movement);
    verticalLayout->addWidget(leftButton);
    verticalLayout->addWidget(rightButton);
    verticalLayout->addWidget(forwardButton);
    verticalLayout->addWidget(backwardButton);
    verticalLayout->addWidget(sinkButton);
    verticalLayout->addWidget(riseButton);
    verticalLayout->addSpacing(20);//Spacing size of 20 pixels

    verticalLayout->addWidget(specialActions);
    verticalLayout->addWidget(surfaceButton);
    verticalLayout->addWidget(fireTorpedoButton);
    verticalLayout->addWidget(fireGrabberButton);
    verticalLayout->addSpacing(20);//Spacing size of 20 pixels

    verticalLayout->addWidget(systemActions);
    verticalLayout->addWidget(menuButton);
    verticalLayout->addWidget(exitButton);
    verticalLayout->addSpacing(20);

    verticalLayout->addWidget(depthReading);
    verticalLayout->addWidget(yawReading);
    verticalLayout->addWidget(accelReading);

    verticalLayout->addSpacing(200);//Spacing size of 200 pixels

    mainLayout->addSpacing(800);
    mainLayout->addLayout(verticalLayout);
    this->setLayout(mainLayout);
}


void ShowCaseView::initialize_VC_Connection(Controller *controller) {
    //Test code to check view and controller connection capabilities
    //Links the 1st 3 buttons of view to controller's first tasks. TaskCCR, TaskHeyTonight, TaskHelloWorld

    //Create holder functions since having trouble with task* - QObject * conversions

    QuickTaskAdder *qta = new QuickTaskAdder();
    qta->initializeQuickTaskAdder(controller);

    connect(leftButton, SIGNAL(clicked()), controller, SLOT(handleMoveLeftButtonClick()));
    connect(rightButton, SIGNAL(clicked()), controller, SLOT(handleMoveRightButtonClick()));
    connect(forwardButton, SIGNAL(clicked()), controller, SLOT(handleMoveForwardButtonClick()));
    connect(backwardButton, SIGNAL(clicked()), controller, SLOT(handleMoveBackwardButtonClick()));
    connect(sinkButton, SIGNAL(clicked()), controller, SLOT(handleSinkButtonClick()));
    connect(riseButton, SIGNAL(clicked()), controller, SLOT(handleRiseButtonClick()));
    connect(exitButton, SIGNAL(clicked()), controller, SLOT(killAll()));


}

