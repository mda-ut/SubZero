#include "SimulatorEngine.h"

SimulatorEngine::SimulatorEngine() {

}

SimulatorEngine::SimulatorEngine(QWidget* container, QWindow *window, SimulatedSub *simSub, SimulatedEnvironment *simEnvironment, Qt3D::QEntity *rootEntity) {
    this->window = window;
    this->simSub = simSub;
    this->simEnvironment = simEnvironment;
    this->rootEntity = rootEntity;
    this->container = container;
}

SimulatorEngine::~SimulatorEngine() {
    delete simEnvironment;
    delete simSub;
    //delete rootEntity;
    renderAspect->renderShutdown();
    engine->shutdown();
    delete logger;
}

void SimulatorEngine::initialize() {
    //Engine Setup
    engine = new Qt3D::QAspectEngine();

    //Setup the sub
    simSub->initialize();

    //Setup the environment
    simEnvironment->initialize();

    //Add Aspects
    renderAspect = new Qt3D::QRenderAspect();
    engine->registerAspect(renderAspect);
    frontCameraInput = new Qt3D::QInputAspect();
    engine->registerAspect(frontCameraInput);
    downCameraInput = new Qt3D::QInputAspect();
    engine->registerAspect(downCameraInput);
    engine->initialize();

    //Engine Window (view) connection
    data = new QVariantMap;
    data->insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(window)));
    data->insert(QStringLiteral("eventSource"), QVariant::fromValue(window));
    engine->setData(*data);

    //Camera Setup
    cameraColor = QColor(0,100,145,100);
    frontCameraInput->setCamera(simSub->frontCamera);
    downCameraInput->setCamera(simSub->downCamera);

    //FrameGraph - Controls how renderAspecting is performed using data
    frameGraph = new Qt3D::QFrameGraph();
    simRenderer = new SimFrameGraph();
    simRenderer->initialize();
    simRenderer->setCameras(simSub->frontCamera, simSub->downCamera);
    simRenderer->setClearColor(cameraColor);
    frameGraph->setActiveFrameGraph(simRenderer);

    //Attach frameGraph to root entity
    rootEntity->addComponent(frameGraph);

    //Tell the engine to use the rootEntity
    engine->setRootEntity(rootEntity);

    //Show the window
    container->show();
}

