#ifndef SIMENVENGINE_H
#define SIMENVENGINE_H


#include "windowwidget.h"
#include "subsub.h"
#include "simenv.h"
#include "simframegraph.h"
#include "simpleframegraphtree.h"
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


/**
 * @brief The SimEnvEngine class
 * This class creates and sets up a basic
 * QAspectEngine with dual cameras(as a public
 * entity along with its aspects but not data source)
 * for a SubSub and SimEnv using a WindowWidget
 * as the surface to render and a root entity.
 */



class SimEnvEngine
{
public:

    SimEnvEngine();
    //blank initializer creates own WindowWidget, SubSub, SimEnv and rootEntity
    void initialize();

    //Quick initializer using an overload
    //Useful if you have your own w/e that you want to use and just want this to set up the
    //engine and camera
    void initialize(WindowWidget *newSource, SubSub *newSub, SimEnv *newEnv, Qt3D::QEntity *newRootEntity);




    Qt3D::QAspectEngine *engine;
    Qt3D::QRenderAspect *render;
    Qt3D::QInputAspect *frontCameraInput;
    Qt3D::QInputAspect *downCameraInput;
    QVariantMap *data;
    Qt3D::QFrameGraph *frameGraph;
    SimFrameGraph *simRenderer;
    QColor cameraColor;





    //Setters
    void setWindow( WindowWidget *newSource);
    void setSub(SubSub *newSub);
    void setEnv(SimEnv *newEnv);

    //Getters (Doing only front camera for now)
    WindowWidget *getWindow();
    SubSub *getSub();
    SimEnv *getEnv();







    /**
      * @param source A pointer to the WindowWidget that
      * serves as the data source for the initialized engine
      *
      * @param sub A pointer to the SubSub object that creates and moves
      * the submarine in the simulation
      *
      * @param eng A pointer to the SimEnv used to create the obstacles
      * in the simulation
      *
      * @param rooEntity ... The entity to which all other entity's are
      * connected (and parented given SubSub and SimEnv's implementation
      */


private:

    WindowWidget *source;
    SubSub *sub;
    SimEnv *env;
    Qt3D::QEntity *rootEntity;




};

#endif // SIMENVENGINE_H
