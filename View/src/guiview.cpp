
#include "guiview.h"
#include <QImage>

GuiView::GuiView()
{
    viewFront = new QGraphicsView;
    viewDown = new QGraphicsView;
    scene = new QGraphicsScene;
    pixmap = new QPixmap;
    mainLayout = new QGridLayout;

}

QPixmap *GuiView::makeQPixmap(cv::Mat *imgData)
{
    QPixmap *p=0;

    // http://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-orqpixmap

    //Assuming rgba, need to add a check for other formats and null.

    QImage image(imgData->data, imgData->cols, imgData->rows,
                 imgData->step, QImage::Format_RGB32);

   p->fromImage(image);
   return p;
}

void GuiView::displayUpdate(cv::Mat *img, QGraphicsView *view)
{
    scene->clear();
    pixmap = makeQPixmap(img);
    scene->addPixmap(*pixmap);
    view->setScene(scene);
    view->show();
}

void GuiView::update(cv::Mat *imgLocFront, cv::Mat *imgLocDown, int *sonarLoc)
{
    displayUpdate(imgLocFront,viewFront);
    displayUpdate(imgLocDown, viewDown);
