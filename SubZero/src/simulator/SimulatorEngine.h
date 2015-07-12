#ifndef SIMULATORENGINE_H
#define SIMULATORENGINE_H

#include <QWindow>
#include <QScreen>

//Camera
#include <QCamera>
#include <QCameraLens>
#include <QLookAtTransform>

//3D Engine
#include <QAspectEngine>
#include <QRenderAspect>
#include <QInputAspect>
#include <QForwardRenderer>
#include <QFrameGraph>

#include "SimulatedEnvironment.h"
#include "SimulatedSub.h"
#include "Logger.h"

class SimulatorEngine {
public:
    SimulatorEngine();
    SimulatorEngine(QWindow *window, SimulatedSub *simSub, SimulatedEnvironment *simEnvironment, Qt3D::QEntity* rootEntity);
    ~SimulatorEngine();

    void initialize();

private:
    Logger* logger = new Logger("SimulatorEngine");

    QWindow* window;
    SimulatedSub* simSub;
    SimulatedEnvironment* simEnvironment;
    Qt3D::QEntity* rootEntity;

    Qt3D::QAspectEngine* engine;
    Qt3D::QRenderAspect* renderAspect;
    Qt3D::QInputAspect *inputAspect;
    QVariantMap *data;
    Qt3D::QCamera *forwardCamera;
    Qt3D::QFrameGraph *frameGraph;
    Qt3D::QForwardRenderer *forwardRenderer;

};

#endif // SIMULATORENGINE_H
