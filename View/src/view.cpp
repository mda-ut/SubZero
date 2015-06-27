#include "view.h"
#include <QBrush>

View::View()
{
    initializeView();

}

void View::initializeView()
{
    setWindowTitle("Camera Displays");
    setFixedSize(1000,500);

    frontCameraRect = new QRect(0,0,400,500); //Area in which the front Camera's images will be displayed
    downCameraRect = new QRect(400,0,400,500);// Area in which the downward Camera's images will be displayed

    frontCameraImage = new QImage;
    downCameraImage = new QImage;

}




void View::paintEvent(QPaintEvent *event)
{
    painter = new QPainter;
    painter->begin(this);

    //Setup background
    QBrush background(Qt::white);
    painter->fillRect(event->rect(), background);

    //Draw Camera Images
    painter->drawImage(*frontCameraRect,*frontCameraImage,*frontCameraRect);
    painter->drawImage(*downCameraRect, *downCameraImage, *frontCameraRect);
    painter->end();
}
