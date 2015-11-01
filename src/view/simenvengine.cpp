#include "simenvengine.h"

SimEnvEngine::SimEnvEngine()
{

}

void SimEnvEngine::initialize()
{


    cameraColor = QColor(0,100,145,100);

    //Window *view = new Window();
    source = new WindowWidget;
    source->initialize();


    //Engine Setup
    engine = new Qt3D::QAspectEngine;

        //Add Aspects
    render = new Qt3D::QRenderAspect;
    engine->registerAspect(render);
    frontCameraInput = new Qt3D::QInputAspect;
    engine->registerAspect(frontCameraInput);
    downCameraInput = new Qt3D::QInputAspect;
    engine->registerAspect(downCameraInput);
    engine->initialize();


        //Engine Window (view) connection
    data = new QVariantMap;
    data->insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(source->getWindow() )));
    data->insert(QStringLiteral("eventSource"), QVariant::fromValue(source->getWindow() ));
    engine->setData(*data);

    //root Entity
    rootEntity = new Qt3D::QEntity;

    //Setup the sub
    sub = new SubSub;
    sub->initialize(rootEntity);

    //Setup the environment
    env = new SimEnv;
    env->initialize(rootEntity);


    //Attach Camera to aspect and aspectEngine
    frontCameraInput->setCamera(sub->frontCamera);
    downCameraInput->setCamera(sub->downCamera);

    //FrameGraph - Controls how rendering is performed using data (buffers, cameras)

    frameGraph = new Qt3D::QFrameGraph();
    simRenderer = new SimFrameGraph;
    simRenderer->initialize();
    simRenderer->setCameras(sub->frontCamera,sub->downCamera);
    simRenderer->setClearColor(cameraColor);
    frameGraph->setActiveFrameGraph(simRenderer);


    //Attach frameGraph to root entity
    rootEntity->addComponent(frameGraph);

    //Tell the engine to use the rootEntity
    engine->setRootEntity(rootEntity);

    //Show the window
    source->show();
}








void SimEnvEngine::initialize(WindowWidget *newSource, SubSub *newSub, SimEnv *newEnv, Qt3D::QEntity *newRootEntity)
{
    cameraColor = QColor(0,100,145,100);

    //Window *view = new Window();
    source = newSource;
    source->initialize();


    //Engine Setup
    engine = new Qt3D::QAspectEngine;

        //Add Aspects
    render = new Qt3D::QRenderAspect;
    engine->registerAspect(render);
    frontCameraInput = new Qt3D::QInputAspect;
    engine->registerAspect(frontCameraInput);
    downCameraInput = new Qt3D::QInputAspect;
    engine->registerAspect(downCameraInput);
    engine->initialize();


        //Engine Window (view) connection
    data = new QVariantMap;
    data->insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(source->getWindow() )));
    data->insert(QStringLiteral("eventSource"), QVariant::fromValue(source->getWindow() ));
    engine->setData(*data);

    //root Entity
    rootEntity = newRootEntity;

    //Setup the sub
    sub = newSub;
    sub->initialize(rootEntity);

    //Setup the environment
    env = newEnv;
    env->initialize(rootEntity);

    //Attach camera to aspect and aspectEngine
    frontCameraInput->setCamera(sub->frontCamera);
    downCameraInput->setCamera(sub->downCamera);

    //FrameGraph - Controls how rendering is performed using data
    frameGraph = new Qt3D::QFrameGraph();
    simRenderer = new SimFrameGraph;
    simRenderer->initialize();
    simRenderer->setCameras(sub->frontCamera, sub->downCamera);
    simRenderer->setClearColor(cameraColor);
    frameGraph->setActiveFrameGraph(simRenderer);



    //Attach frameGraph to root entity
    rootEntity->addComponent(frameGraph);



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
