#include "View.h"
#include <QBrush>
#include <opencv2/imgproc.hpp>

View::View()
{
    initializeView();
}

View::View(std::vector<State *> states_) {
    states = states_;
    initializeView();
}

View::~View(){

}

void View::update(int ID) {

}

void View::initializeView()
{
    setWindowTitle("Camera Displays");
    setFixedSize(1000,500);

    frontCameraRect.setRect(0,0,400,500); //Area in which the front Camera's images will be displayed
    downCameraRect.setRect(400,0,400,500);// Area in which the downward Camera's images will be displayed
}

void View::makeQImage(cv::Mat imgData, QImage& imgHolder)
{
    imgHolder = QImage((uchar*)imgData.data, imgData.cols, imgData.rows, imgData.step, QImage::Format_RGB888);
}

void View::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //std::cout<<"painting"<<std::endl;
    //Setup background
    QBrush background(Qt::white);
    painter.fillRect(event->rect(), background);

    //Draw Camera Images
    painter.drawImage(frontCameraRect, frontCameraImage, frontCameraRect);
    painter.drawImage(downCameraRect, downCameraImage, frontCameraRect);
}
