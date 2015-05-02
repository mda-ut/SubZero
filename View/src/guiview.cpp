
/*
 * view.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: edem
 */

#ifndef GUIVIEW_H
#define GUIVIEW_H

#include "view.h"
#include "observer.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPaintEvent>
#include <QGridLayout>
#include <QWidget>
#include <cv.h>
#include <highgui.h>



/** The GuiView class creates a GUI
 * to allow interaction with the
 * controller.
 */


class GuiView : public View, public Observer
{
public:
    GuiView();

    QGraphicsView *viewFront;
    QGraphicsView *viewDown;
    QGraphicsScene *scene;
    QPixmap *pixmap;
    QGridLayout *mainLayout;
    QPaintEvent *paintEvent;


    QPixmap *makeQPixmap(cv::Mat* imgData);
    void displayUpdate (cv::Mat* img, QGraphicsView *view);
    void update(cv::Mat* imgLocFront,cv::Mat* imgLocDown , int* sonarLoc);
};

#endif // GUIVIEW_H
