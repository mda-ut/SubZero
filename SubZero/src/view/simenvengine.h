#ifndef SIMENVENGINE_H
#define SIMENVENGINE_H


#include "windowwidget.h"
#include "subsub.h"
#include "simenv.h"
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


/**
 * @brief The SimEnvEngine class
 * This class creates and sets up a basic
 * QAspectEngine (as a public entity along with its aspects but not data source)
 * for a SubSub and SimEnv using a WindowWidget
 * as the surface to render and a root entity.
 * The basic renderer is a forward renderer but the
 * framegraph can be directly accessed (public) to change
 * the renderer.
 *
 *
 * This allows two SimEnvEngines to be called using the same source
 * and then have their cameras  in different locations
 * It is possible that the same functionality can be achieved by just adding
 * another camera and framegraph (and renderer)
 *
 *
 * NOTE: You do not need to call initialize for the classes used to initialize
 * this class. They are automatically initialized using the rootEntity passed in
 * //What happens if you initialize something that's already initialized
 * //I don't think anything should (apart from some memory leakage b/c you're
 * // calling new again. LOOK INTO THIS
 *
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
    Qt3D::QInputAspect *input;
    QVariantMap *data;
    Qt3D::QCamera *camera;
    Qt3D::QFrameGraph *frameGraph;
    Qt3D::QForwardRenderer *forwardRenderer;

    /**
     * Query:
     * Why am I not using Q-PROPERTY
     *
     * Response:
     * I don't know. Don't plan on animating?
     * :/
     *
     * I don't want to inherit from QObject b/c
     * no need for signals and slots... so no moc required
     *
     * Yup, that sounds better.
     */

    //Setters
    void setWindow( WindowWidget *newSource);
    void setSub(SubSub *newSub);
    void setEnv(SimEnv *newEnv);

    //Getters
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
