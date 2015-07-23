#ifndef SIMULATORENGINE_H
#define SIMULATORENGINE_H

#include <QWindow>
#include <QWidget>
#include <QScreen>

//Camera
#include <QCamera>
#include <QCameraLens>
#include <QLookAtTransform>

//3D Engine
#include <QAspectEngine>
#include <QRenderAspect>
#include <QInputAspect>
#include <QFrameGraph>

#include "SimulatedEnvironment.h"
#include "SimulatedSub.h"
#include "SimFrameGraph.h"
#include "Logger.h"

class SimulatorEngine {
public:
    SimulatorEngine();
    SimulatorEngine(QWidget* container, QWindow *window, SimulatedSub *simSub, SimulatedEnvironment *simEnvironment, Qt3D::QEntity* rootEntity);
    ~SimulatorEngine();

    void initialize();

private:
    Logger* logger = new Logger("SimulatorEngine");
    QWidget* container;
    QWindow* window;
    SimulatedSub* simSub;
    SimulatedEnvironment* simEnvironment;
    Qt3D::QEntity* rootEntity;

    Qt3D::QAspectEngine* engine;
    Qt3D::QRenderAspect* renderAspect;
    Qt3D::QInputAspect* frontCameraInput;
    Qt3D::QInputAspect* downCameraInput;
    QVariantMap *data;
    Qt3D::QFrameGraph *frameGraph;
    SimFrameGraph* simRenderer;
    QColor cameraColor;

};

#endif // SIMULATORENGINE_H
