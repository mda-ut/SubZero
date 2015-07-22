#ifndef SIMBUFFERWINDOW_H
#define SIMBUFFERWINDOW_H

#include <QWindow>
#include <QWidget>
#include "Logger.h"
#include "SimulatorEngine.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class SimBufferWindow : public QWidget{
public:
    SimBufferWindow(SimulatedSub* simSub, SimulatedEnvironment* simEnv, Qt3D::QEntity* rootEntity);
    ~SimBufferWindow();

    virtual void update(int id);
    virtual void initialize();

    QWindow* getWindow();
    cv::Mat getImg();

private:
    Logger* logger = new Logger("SimBufferWindow");

    SimulatorEngine* engine;
    SimulatedSub* simSub;
    SimulatedEnvironment* simEnv;
    Qt3D::QEntity* rootEntity;

    QWidget* container;
    QWindow* window;
    QSurfaceFormat* format;

};

#endif // SIMBUFFERWINDOW_H
