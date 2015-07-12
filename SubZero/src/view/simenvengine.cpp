#include "simenvengine.h"

SimEnvEngine::SimEnvEngine()
{

}

void SimEnvEngine::initialize()
{
    //Window *view = new Window();
    source = new WindowWidget;
    source->initialize();


    //Engine Setup
    engine = new Qt3D::QAspectEngine;

        //Add Aspects
    render = new Qt3D::QRenderAspect;
    engine->registerAspect(render);
    input = new Qt3D::QInputAspect;
    engine->registerAspect(input);
    engine->initialize();


        //Engine Window (view) connection
    data = new QVariantMap;
    data->insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(source->getWindow() )));
    data->insert(QStringLiteral("eventSource"), QVariant::fromValue(source->getWindow() ));
    engine->setData(*data);

    //root Entity
    rootEntity = new Qt3D::QEntity;

    //Camera Setup
    camera = new Qt3D::QCamera(rootEntity);
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0.0f, 0.0f , -20.0f));
    camera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    //Attach camera to aspect and aspectEngine
    input->setCamera(camera);

    //FrameGraph - Controls how rendering is performed using data
    frameGraph = new Qt3D::QFrameGraph();
    forwardRenderer = new Qt3D::QForwardRenderer();

    forwardRenderer->setCamera(camera);
    forwardRenderer->setClearColor(Qt::white);
    frameGraph->setActiveFrameGraph(forwardRenderer);


    //Attach frameGraph to root entity
    rootEntity->addComponent(frameGraph);

    //Setup the sub
    sub = new SubSub;
    sub->initialize(rootEntity);

    //Setup the environment
    env = new SimEnv;
    env->initialize(rootEntity);

    //Tell the engine to use the rootEntity
    engine->setRootEntity(rootEntity);



    //Show the window
    source->show();

}








void SimEnvEngine::initialize(WindowWidget *newSource, SubSub *newSub, SimEnv *newEnv, Qt3D::QEntity *newRootEntity)
{
    //Window *view = new Window();
    source = newSource;
    source->initialize();


    //Engine Setup
    engine = new Qt3D::QAspectEngine;

        //Add Aspects
    render = new Qt3D::QRenderAspect;
    engine->registerAspect(render);
    input = new Qt3D::QInputAspect;
    engine->registerAspect(input);
    engine->initialize();


        //Engine Window (view) connection
    data = new QVariantMap;
    data->insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(source->getWindow() )));
    data->insert(QStringLiteral("eventSource"), QVariant::fromValue(source->getWindow() ));
    engine->setData(*data);

    //root Entity
    rootEntity = newRootEntity;

    //Camera Setup
    camera = new Qt3D::QCamera(rootEntity);
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0.0f, 0.0f , -20.0f));
    camera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    //Attach camera to aspect and aspectEngine
    input->setCamera(camera);

    //FrameGraph - Controls how rendering is performed using data
    frameGraph = new Qt3D::QFrameGraph();
    forwardRenderer = new Qt3D::QForwardRenderer();

    forwardRenderer->setCamera(camera);
    forwardRenderer->setClearColor(Qt::white);
    frameGraph->setActiveFrameGraph(forwardRenderer);


    //Attach frameGraph to root entity
    rootEntity->addComponent(frameGraph);

    //Setup the sub
    sub = newSub;
    sub->initialize(rootEntity);

    //Setup the environment
    env = newEnv;
    env->initialize(rootEntity);

    //Tell the engine to use the rootEntity
    engine->setRootEntity(rootEntity);



    //Show the window
    source->show();

}








void SimEnvEngine::setWindow(WindowWidget *newSource)
{
    source = newSource;
}

void SimEnvEngine::setSub(SubSub *newSub)
{
    sub = newSub;
}

void SimEnvEngine::setEnv(SimEnv *newEnv)
{
    env = newEnv;
}

WindowWidget *SimEnvEngine::getWindow()
{
    return source;
}

SubSub *SimEnvEngine::getSub()
{
    return sub;
}

SimEnv *SimEnvEngine::getEnv()
{
    return env;
}

