#ifndef SIMBUFFERWINDOW_H
#define SIMBUFFERWINDOW_H

#include <QWindow>
#include <QWidget>
#include <QLabel>
#include <QMutex>
#include "Logger.h"
#include "SimulatorEngine.h"
#include "Properties.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class SimBufferWindow : public QWidget {
    Q_OBJECT
public:
    SimBufferWindow(SimulatedSub* simSub, SimulatedEnvironment* simEnv, Qt3D::QEntity* rootEntity, Properties* properties);
    ~SimBufferWindow();

    virtual void update(int id);
    virtual void initialize();

    QWindow* getWindow();
    cv::Mat getImg(int position);

signals:
    void grabWidget(int position);

private slots:
    void updatePixmap(int position);

private:
    Logger* logger = new Logger("SimBufferWindow");

    SimulatorEngine* engine;
    SimulatedSub* simSub;
    SimulatedEnvironment* simEnv;
    Qt3D::QEntity* rootEntity;

    QWidget* container;
    QWindow* window;
    QSurfaceFormat* format;
    QPixmap pixmap;
    Properties* properties;
    int downCam;
    int frontCam;
    bool pixmapSet;

    QMutex mutex;



};

#endif // SIMBUFFERWINDOW_H
