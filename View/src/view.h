#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QRect>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
//#include "observer.h"    //Need a concerte observer class
#include <cv.h>
#include <highgui.h>


using namespace cv;


/**
 * Updates the view class by using painter.drawImage (in paintEvent) to
 * display the camera images as a lower quality alternative
 * to the pixmap QGraphics Scene method. This is preferable
 * as the previous method was largely resource intensive and
 * consisted of more steps.
 *
 *
 * This class is responsible for the setting up the image. The data for the
 * views (with the exception of autonomous) is handled in the Observer
 * class.
 */




/**
  * @param frontCameraRect  Holds the rectangle in which the image from the front
  * camera is drawn
  * @param downCameraRect  Holds the rectangle in which the image from the downwards
  * camera is drawn
  *
  * @param painter Performs all the painting on the window of the view through
  * the paintEvent function/routine
  *
  * @param makeQImage used to display the image on the views
  *
  */

//Ignoring the inheritance from observer until I place this back in view

class View: public QWidget
{
    Q_OBJECT

public:
    View();

    QImage *frontCameraImage;
    QImage *downCameraImage;

private:
    void initializeView();
    QRect *frontCameraRect;
    QRect *downCameraRect;

    QPainter *painter;

    void paintEvent(QPaintEvent *event); //All drawing and painting will take place in here

    //From View
    virtual void makeQImage(Mat *imgData, QImage *imgHolder)=0; //Converting Mat to QImage //Creating camera image, overload

};

#endif // VIEW2_H
