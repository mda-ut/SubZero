#ifndef GUIVIEW_H
#define GUIVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRect>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QSize>
#include <cv.h>
#include <highgui.h>
#include <vector>

#include "Logger.h"
#include "View.h"

class GUIView : public View {
public:
    GUIView();
    GUIView(Stage* stage, Controller* controller, std::vector<State*> states);
    ~GUIView();

    virtual void update(int id);
    virtual void initialize();
    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;

protected:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);

private:
    Logger* logger = new Logger("GUIView");

    QRect frontCameraRect;
    QRect downCameraRect;
    QImage frontCameraImage;
    QImage downCameraImage;

    QLabel* powerStatus;
    QPushButton *powerButton;
    QPushButton *motorButton;

    QLabel* movement;
    QPushButton *leftButton;
    QPushButton *rightButton;

    QPushButton *forwardButton;
    QPushButton *backwardButton;
    QPushButton *sinkButton;
    QPushButton *riseButton;
    QPushButton *stopButton;

    QLabel* specialActions;
    QPushButton *surfaceButton;
    QPushButton *gateButton;
    QPushButton *pathButton;

    QLabel* systemActions;
    QPushButton *menuButton;
    QPushButton *exitButton;

    QLabel* depthReading;
    QLabel* yawReading;

    QLabel* targetDepthLabel;
    QLabel* targetYawLabel;

    void makeQImage(cv::Mat imgData, QImage& imgHolder);
};

#endif // GUIVIEW_H
