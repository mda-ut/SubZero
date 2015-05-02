#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPaintEvent>
#include <QGridLayout>
#include <QWidget>
#include <cv.h>
#include <highgui.h>

/** This abstract class holds the basic
 * properties expected of all views -a
 * display via QGraphics, QPixmap, QPainters
 * andlayouts; and Signals and slots
 *
 */

class View :public QWidget
{
    Q_OBJECT
public:
    View();

    QGraphicsView *viewFront;
    QGraphicsView *viewDown;
    QGraphicsScene *scene;
    QPixmap *pixmap;
    QGridLayout *mainLayout;
    QPaintEvent *paintEvent;

    /** makeQPixmap converts the opencv Mat
     * object into a QPixmap.
     * displayImage updates the scene with a
     * pixmap to be displayed
     */

    virtual QPixmap* makeQPixmap(cv::Mat* img)=0;
    virtual void displayUpdate (cv::Mat* img, QGraphicsScene *view)= 0;
};

#endif // VIEW_H
