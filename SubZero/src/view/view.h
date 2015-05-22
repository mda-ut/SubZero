#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QSize>
#include <QWidget>
#include <QLabel>
#include <cv.h>
#include <highgui.h>

/** This abstract class holds the basic
 * properties expected of all views -a
 * display via QGraphics, QPixmap;
 * and Signals and slots
 *
 */

class View :public QWidget
{
    Q_OBJECT
public:
    View();

    /**
    * @param viewFront 'Screen' of the Front facing camera
    * @param viewDown 'Screen' of the Downwards facing camera
    * @param sceneFront the image to be shown in viewFront
    * @param sceneDown the image to be shown in viewDown
    * @param displaySize the size of the view screens and their scenes
    *
    *
    */

    QGraphicsView *viewFront;
    QGraphicsView *viewDown;
    QGraphicsScene *sceneFront;
    QGraphicsScene *sceneDown;
    QPixmap *pixmap;
    QSize *displaySize;
    QLabel *sonarStrength;

    /**
     * makeQPixmap converts the opencv Mat
     * object into a QPixmap.
     * displayImage updates the scene with a
     * pixmap to be displayed
     */

    virtual QPixmap makeQPixmap(cv::Mat* img)=0;
    virtual void displayUpdate (cv::Mat* img, QGraphicsScene *scene)= 0;
};

#endif // VIEW_H
