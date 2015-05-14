#ifndef GUIVIEW_H
#define GUIVIEW_H

#include "view.h"
#include "observer.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QWidget>
#include <cv.h>
#include <highgui.h>

#include <QComboBox>
#include <QPushButton>
#include <QSize>



/** The GuiView class creates a GUI
 * to allow interaction with the
 * controller.
 */


class GuiView : public View, public Observer
{
public:
    GuiView();

    /**
     * @param actionSelector Holds all view actions
     * @param affirmSelector Actuates current action in
    */


    QComboBox *actionSelector;
    QPushButton *affirmButton;

    QPixmap makeQPixmap(cv::Mat* imgData);
    void displayUpdate (cv::Mat* img, QGraphicsScene *scene);
    void update(cv::Mat* imgLocFront,cv::Mat* imgLocDown , int* sonarLoc);
};

#endif // GUIVIEW_H
