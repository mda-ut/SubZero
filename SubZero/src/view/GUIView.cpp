#include <QCoreApplication>
#include "opencv2/imgproc/types_c.h"
#include "opencv2/imgproc/imgproc.hpp"

#include "GUIView.h"
#include "Stage.h"

GUIView::GUIView() {

}

GUIView::GUIView(Stage* stage, Controller* controller, std::vector<State*> states)
    : View(stage, controller, states) {
}

void GUIView::update(int id) {
    // Update Cameras    logger->trace("Received update from " + std::to_string(ID));
    switch (id) {
        case FRONTCAM: {
            ImgData* newImg = dynamic_cast<CameraState*>(states[0])->getState("raw");
            makeQImage(newImg->img, frontCameraImage);
            logger->trace("Updating front cam image");
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
            int power = newData->getPower();
            int depth = newData->getDepth();
            int yaw = newData->getYaw();

            if (power) {
                powerStatus->setText("Power: On");
            } else {
                powerStatus->setText("Power: Off");
            }
            std::string temp = "Depth: " + std::to_string(depth);
            depthReading->setText(temp.c_str());
            temp = "Yaw: " + std::to_string(yaw);
            yawReading->setText(temp.c_str());
            break;
        }
    }
    QWidget::update();
}

void GUIView::initialize() {
    setFixedSize(1250, 700);
    setWindowTitle("GUIView");

    frontCameraRect.setRect(525,0,525,700);
    downCameraRect.setRect(0,0,525,700);

    //frontCameraImage = QImage(":/img/MDA.jpg");

    //Creating an image that holds a gradient of blue

    //Create an image to be painted on
    QImage sub(525,700,QImage::Format_RGB32);

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
    //subImgPainter.fillRect(sub.rect(), blueGradientBrush);
    //subImgPainter.end();

    downCameraImage = sub;

    // Show Case View Widget initialization
    powerStatus = new QLabel("Power: Off");
    powerButton = new QPushButton("Turn Power On/Off");
    powerButton->setCheckable(true);
    motorButton = new QPushButton("Turn Motors On");

    movement = new QLabel("Movement");
    leftButton = new QPushButton("Veer Left");
    rightButton = new QPushButton("Veer right");

    forwardButton = new QPushButton("Move Forward");
    backwardButton = new QPushButton("Move Backward");
    sinkButton = new QPushButton("Sink");
    riseButton = new QPushButton("Rise");
    stopButton = new QPushButton("Stop");

    specialActions = new QLabel("Special Actions");
    surfaceButton = new QPushButton("Surface");
    gateButton = new QPushButton("Gate Task");
    pathButton = new QPushButton("Path Task");

    systemActions = new QLabel("System Actions");
    menuButton = new QPushButton("Menu");
    exitButton = new QPushButton("Exit");

    depthReading = new QLabel("Depth:");
    yawReading = new QLabel("Yaw:");

    targetDepthLabel = new QLabel("Target:");
    targetYawLabel = new QLabel("Target:");

    // Show Case View layouts
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QGridLayout *readingsLayout = new QGridLayout();

    //Show Case view Widget Positioning
    //Down want to add rects from view to layout
    //What to do? : set other BoxLayouts and add spacing?

    verticalLayout->addWidget(powerStatus);
    verticalLayout->addWidget(powerButton);
    verticalLayout->addWidget(motorButton);
    verticalLayout->addSpacing(10);

    verticalLayout->addWidget(movement);
    verticalLayout->addWidget(leftButton);
    verticalLayout->addWidget(rightButton);
    verticalLayout->addWidget(sinkButton);
    verticalLayout->addWidget(riseButton);
    verticalLayout->addWidget(forwardButton);
    verticalLayout->addWidget(backwardButton);
    verticalLayout->addWidget(stopButton);
    verticalLayout->addSpacing(10); //Spacing size of 20 pixels

    verticalLayout->addWidget(specialActions);
    verticalLayout->addWidget(surfaceButton);
    verticalLayout->addWidget(gateButton);
    verticalLayout->addWidget(pathButton);
    verticalLayout->addSpacing(10); //Spacing size of 20 pixels

    verticalLayout->addWidget(systemActions);
    verticalLayout->addWidget(menuButton);
    verticalLayout->addWidget(exitButton);
    verticalLayout->addSpacing(10);

    readingsLayout->addWidget(yawReading, 0, 0, Qt::AlignLeft);
    readingsLayout->addWidget(targetYawLabel, 0, 1, Qt::AlignLeft);
    readingsLayout->addWidget(depthReading, 1, 0, Qt::AlignLeft);
    readingsLayout->addWidget(targetDepthLabel, 1, 1, Qt::AlignLeft);
    verticalLayout->addLayout(readingsLayout);


    mainLayout->addSpacing(1150);
    mainLayout->addLayout(verticalLayout);
    this->setLayout(mainLayout);

    // Setup connections
    connect(powerButton, SIGNAL(clicked()), controller, SLOT(handlePowerButtonToggled()));
    connect(motorButton, SIGNAL(clicked()), controller, SLOT(handleMotorButtonClick()));
    connect(leftButton, SIGNAL(clicked()), controller, SLOT(handleMoveLeftButtonClick()));
    connect(rightButton, SIGNAL(clicked()), controller, SLOT(handleMoveRightButtonClick()));
    connect(sinkButton, SIGNAL(clicked()), controller, SLOT(handleSinkButtonClick()));
    connect(riseButton, SIGNAL(clicked()), controller, SLOT(handleRiseButtonClick()));
    connect(forwardButton, SIGNAL(clicked()), controller, SLOT(handleMoveForwardButtonClick()));
    connect(backwardButton, SIGNAL(clicked()), controller, SLOT(handleMoveBackwardButtonClick()));
    connect(stopButton, SIGNAL(clicked()), controller, SLOT(handleStopButtonClick()));
    connect(gateButton, SIGNAL(clicked()), controller, SLOT(handleGateTaskClick()));
    connect(pathButton, SIGNAL(clicked()), controller, SLOT(handlePathTaskClick()));
    connect(menuButton, SIGNAL(clicked()), stage, SLOT(switchToMenuView()));
    connect(exitButton, SIGNAL(clicked()), stage, SLOT(exit()));
}

QSize GUIView::sizeHint() const {
    return QSize(1250,700);
}

QSize GUIView::minimumSizeHint() const {
    return QSize(1250,700);
}

void GUIView::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_AsciiCircum:
        powerButton->click();
        break;
    case Qt::Key_Percent:
        motorButton->click();
        break;
    case Qt::Key_W:
        forwardButton->click();
        break;
    case Qt::Key_A:
        leftButton->click();
        break;
    case Qt::Key_S:
        backwardButton->click();
        break;
    case Qt::Key_D:
        rightButton->click();
        break;
    case Qt::Key_R:
        riseButton->click();
        break;
    case Qt::Key_F:
        sinkButton->click();
        break;
    case Qt::Key_E:
        stopButton->click();
        break;
    case Qt::Key_1:
        gateButton->click();
        break;
    case Qt::Key_2:
        pathButton->click();
        break;
    case Qt::Key_Q:
        exitButton->click();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void GUIView::makeQImage(cv::Mat imgData, QImage& imgHolder) {
    switch (imgData.type())
    {
        // 8-bit, 4 channel
        case CV_8UC4: {
            imgHolder = QImage( imgData.data, imgData.cols, imgData.rows, imgData.step, QImage::Format_RGB32 );
            break;
        }
            // 8-bit, 3 channel
        case CV_8UC3: {
            imgHolder = QImage( imgData.data, imgData.cols, imgData.rows, imgData.step, QImage::Format_RGB888 );
            break;
        }
            // 8-bit, 1 channel
        case CV_8UC1: {
            static QVector<QRgb>  sColorTable;

            // only create our color table once
            if (sColorTable.isEmpty()) {
                for ( int i = 0; i < 256; ++i ) {
                    sColorTable.push_back( qRgb( i, i, i ) );
                }
            }

            imgHolder = QImage( imgData.data, imgData.cols, imgData.rows, imgData.step, QImage::Format_Indexed8 );
            imgHolder.setColorTable( sColorTable );
            break;
        }
        default:
            logger->warn("cvMatToQImage() - cv::Mat image type not handled in switch: " + std::to_string(imgData.type()));
            break;
    }
}

void GUIView::paintEvent(QPaintEvent *event) {

    QPainter painter;
    painter.begin(this);
    // Setup background
    QBrush background(Qt::white);
    painter.fillRect(event->rect(), background);

    // Draw Camera Images
    painter.drawImage(frontCameraRect, frontCameraImage, frontCameraRect);
    painter.drawImage(downCameraRect, downCameraImage, downCameraRect);
    painter.end();
}

GUIView::~GUIView() {
    delete logger;
}
