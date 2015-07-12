#include "SimulatorEngine.h"

SimulatorEngine::SimulatorEngine() {

}

SimulatorEngine::SimulatorEngine(QWindow *window, SimulatedSub *simSub, SimulatedEnvironment *simEnvironment, Qt3D::QEntity *rootEntity) {
    this->window = window;
    this->simSub = simSub;
    this->simEnvironment = simEnvironment;
    this->rootEntity = rootEntity;
}

SimulatorEngine::~SimulatorEngine() {
    delete logger;
}

void SimulatorEngine::initialize() {
    //Engine Setup
    engine = new Qt3D::QAspectEngine();

    //Add Aspects
    renderAspect = new Qt3D::QRenderAspect();
    engine->registerAspect(renderAspect);
    inputAspect = new Qt3D::QInputAspect();
    engine->registerAspect(inputAspect);
    engine->initialize();

    //Engine Window (view) connection
    data = new QVariantMap;
    data->insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(window)));
    data->insert(QStringLiteral("eventSource"), QVariant::fromValue(window));
    engine->setData(*data);

    //Camera Setup
    forwardCamera = new Qt3D::QCamera(rootEntity);
    forwardCamera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    forwardCamera->setPosition(QVector3D(0.0f, 0.0f , -20.0f));
    forwardCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    forwardCamera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    //Attach forwardCamera to aspect and aspectEngine
    inputAspect->setCamera(forwardCamera);

    //FrameGraph - Controls how renderAspecting is performed using data
    frameGraph = new Qt3D::QFrameGraph();
    forwardRenderer = new Qt3D::QForwardRenderer();

    forwardRenderer->setCamera(forwardCamera);
    forwardRenderer->setClearColor(Qt::white);
    frameGraph->setActiveFrameGraph(forwardRenderer);

    //Attach frameGraph to root entity
    rootEntity->addComponent(frameGraph);

    //Setup the sub
    simSub->initialize();

    //Setup the environment
    simEnvironment->initialize();

    //Tell the engine to use the rootEntity
    engine->setRootEntity(rootEntity);

    //Show the window
    window->show();
}

