#include "View.h"
#include <QBrush>

View::View()
{
    initializeView();
}

View::View(std::vector<State *> states_) {
    states = states_;
}

View::~View(){

}

void View::update(int ID) {

}

void View::initializeView()
{
    setWindowTitle("Camera Displays");
    setFixedSize(1000,500);

    frontCameraRect = new QRect(0,0,400,500); //Area in which the front Camera's images will be displayed
    downCameraRect = new QRect(400,0,400,500);// Area in which the downward Camera's images will be displayed
}

void View::makeQImage(cv::Mat imgData, QImage& imgHolder)
{
    imgHolder = QImage(imgData.data, imgData.cols, imgData.rows,QImage::Format_RGB32);
}

void View::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    //Setup background
    QBrush background(Qt::white);
    painter.fillRect(event->rect(), background);

    //Draw Camera Images
    painter.drawImage(*frontCameraRect,frontCameraImage,*frontCameraRect);
    painter.drawImage(*downCameraRect, downCameraImage, *frontCameraRect);
    painter.end();
}
