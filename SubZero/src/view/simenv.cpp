#include "simenv.h"
#include <QString>
#include <QUrl>
#include <QColor>
#include <QRgb>


SimEnv::SimEnv()
{

}

void SimEnv::initialize(Qt3D::QEntity *rootEntity)
{

    //Create entities for all objects in the simulation
    yellowBuoyEntity = new Qt3D::QEntity;
    blueBuoyEntity = new Qt3D::QEntity;
    redBuoyEntity = new Qt3D::QEntity;
    greenBuoyEntity = new Qt3D::QEntity;

    setDateEntity = new Qt3D::QEntity;
    timePortalEntity = new Qt3D::QEntity;
    guideMarkerEntity = new Qt3D::QEntity;


    //Create URLs from the files in the reource folder (or using root directory)
    //Needs to be URL set from qrc file can't just use string to set the source for the mesh


    //Set up the meshes using the blend files via QUrl's
    yellowBuoyBody = new Qt3D::QMesh;
    yellowBuoyBody->setSource( QUrl("qrc:/mdl/simViewModelItems/Obj Model Files/Yellow Buoy.obj") );

    blueBuoyBody = new Qt3D::QMesh;
    blueBuoyBody->setSource( QUrl( "qrc:/mdl/simViewModelItems/Obj Model Files/Blue Buoy.obj") );

    redBuoyBody = new Qt3D::QMesh;
    redBuoyBody->setSource(QUrl("qrc:/mdl/simViewModelItems/Obj Model Files/Red Buoy.obj") );

    greenBuoyBody = new Qt3D::QMesh;
    greenBuoyBody->setSource( QUrl( "qrc:/mdl/simViewModelItems/Obj Model Files/Green Buoy.obj") );

    setDateBody = new Qt3D::QMesh;
    setDateBody->setSource(QUrl("qrc:/mdl/simViewModelItems/Obj Model Files/Set Date.obj"));

    timePortalBody = new Qt3D::QMesh;
    timePortalBody->setSource(QUrl("qrc:/mdl/simViewModelItems/Obj Model Files/Time Portal.obj"));

    guideMarkerBody = new Qt3D::QMesh;
    guideMarkerBody->setSource(QUrl( "qrc:/mdl/simViewModelItems/Obj Model Files/Guide Marker.obj"));



    //Setting up the materials
    yellowBuoyMaterial = new Qt3D::QPhongMaterial;
    yellowBuoyMaterial->setDiffuse( QColor(100,100,0)  );


    blueBuoyMaterial = new Qt3D::QPhongMaterial;
    blueBuoyMaterial->setDiffuse( QColor(0,0,100)  );



    redBuoyMaterial = new Qt3D::QPhongMaterial;
    redBuoyMaterial->setDiffuse( QColor(100,0,0)  );

    greenBuoyMaterial = new Qt3D::QPhongMaterial;
    greenBuoyMaterial->setDiffuse( QColor(0,100,0)  );

    setDateMaterial = new Qt3D::QPhongMaterial;
    setDateMaterial->setDiffuse( QColor(125,125,0)  );

    timePortalMaterial = new Qt3D::QPhongMaterial;
    timePortalMaterial->setDiffuse( QColor(0,150,0)  );

    guideMarkerMaterial = new Qt3D::QPhongMaterial;
    guideMarkerMaterial->setDiffuse( QColor(125,60,0)  );



    //Setup initial positions usign QTranslateTransform
    yellowBuoyTranslation = new Qt3D::QTranslateTransform;
    yellowBuoyTranslation-> setTranslation(   QVector3D(10.0f, 10.0f, 80.0f)     );

    blueBuoyTranslation = new Qt3D::QTranslateTransform;
    blueBuoyTranslation-> setTranslation(   QVector3D(0.0f, 10.0f, 80.0f)     );

    redBuoyTranslation = new Qt3D::QTranslateTransform;
    redBuoyTranslation-> setTranslation(   QVector3D(20.0f, 10.0f, 80.0f)     );

    greenBuoyTranslation = new Qt3D::QTranslateTransform;
    greenBuoyTranslation-> setTranslation(   QVector3D(30.0f, 10.0f, 80.0f)     );

    setDateTranslation = new Qt3D::QTranslateTransform;
    setDateTranslation-> setTranslation(   QVector3D(50.0f, 0.0f, 80.0f)     );

    timePortalTranslation = new Qt3D::QTranslateTransform;
    timePortalTranslation-> setTranslation(   QVector3D(10.0f, 0.0f, 80.0f)     );

    guideMarkerTranslation = new Qt3D::QTranslateTransform;
    guideMarkerTranslation-> setTranslation(   QVector3D(30.0f, 0.0f, 80.0f)     );




    //Setup Initial Rotation
    yellowBuoyRotation = new Qt3D::QRotateTransform;
    yellowBuoyRotation->setAxis(   QVector3D(1.0f, 0.0f, 0.0f)  );
    yellowBuoyRotation->setAngleDeg(0.0f);


    blueBuoyRotation = new Qt3D::QRotateTransform;
    blueBuoyRotation->setAxis(   QVector3D(1.0f, 0.0f, 0.0f)  );
    blueBuoyRotation->setAngleDeg(0.0f);


    redBuoyRotation = new Qt3D::QRotateTransform;
    redBuoyRotation->setAxis(   QVector3D(1.0f, 0.0f, 0.0f)  );
    redBuoyRotation->setAngleDeg(0.0f);


    greenBuoyRotation = new Qt3D::QRotateTransform;
    greenBuoyRotation->setAxis(   QVector3D(1.0f, 0.0f, 0.0f)  );
    greenBuoyRotation->setAngleDeg(0.0f);


    setDateRotation = new Qt3D::QRotateTransform;
    setDateRotation->setAxis(   QVector3D(1.0f, 0.0f, 0.0f)  );
    setDateRotation->setAngleDeg(0.0f);


    timePortalRotation = new Qt3D::QRotateTransform;
    timePortalRotation->setAxis(   QVector3D(1.0f, 0.0f, 0.0f)  );
    timePortalRotation->setAngleDeg(0.0f);


    guideMarkerRotation = new Qt3D::QRotateTransform;
    guideMarkerRotation->setAxis(   QVector3D(1.0f, 0.0f, 0.0f)  );
    guideMarkerRotation->setAngleDeg(0.0f);



    //Configure Transforms into Transform Components
    yellowBuoyTransform = new Qt3D::QTransform;
    yellowBuoyTransform->addTransform(yellowBuoyTranslation);
    yellowBuoyTransform->addTransform(yellowBuoyRotation);


    blueBuoyTransform = new Qt3D::QTransform;
    blueBuoyTransform->addTransform( blueBuoyTranslation);
    blueBuoyTransform->addTransform( blueBuoyRotation);


    redBuoyTransform = new Qt3D::QTransform;
    redBuoyTransform->addTransform(redBuoyTranslation);
    redBuoyTransform->addTransform(redBuoyRotation);


    greenBuoyTransform = new Qt3D::QTransform;
    greenBuoyTransform->addTransform(greenBuoyTranslation);
    greenBuoyTransform->addTransform(greenBuoyRotation);


    setDateTransform = new Qt3D::QTransform;
    setDateTransform->addTransform(setDateTranslation);
    setDateTransform->addTransform(setDateRotation);


    timePortalTransform = new Qt3D::QTransform;
    timePortalTransform->addTransform(timePortalTranslation);
    timePortalTransform->addTransform(timePortalRotation);


    guideMarkerTransform = new Qt3D::QTransform;
    guideMarkerTransform->addTransform(guideMarkerTranslation);
    guideMarkerTransform->addTransform(guideMarkerRotation);


    //Adding the components to the entities
    //Ready for introduction to the AspectEngine which sets up 3D

    yellowBuoyEntity->addComponent(yellowBuoyBody);
    yellowBuoyEntity->addComponent(yellowBuoyMaterial);
    yellowBuoyEntity->addComponent(yellowBuoyTransform);

    blueBuoyEntity->addComponent(blueBuoyBody);
    blueBuoyEntity->addComponent(blueBuoyMaterial);
    blueBuoyEntity->addComponent(blueBuoyTransform);

    redBuoyEntity->addComponent(redBuoyBody);
    redBuoyEntity->addComponent(redBuoyMaterial);
    redBuoyEntity->addComponent(redBuoyTransform);

    greenBuoyEntity->addComponent(greenBuoyBody);
    greenBuoyEntity->addComponent(greenBuoyMaterial);
    greenBuoyEntity->addComponent(greenBuoyTransform);

    setDateEntity->addComponent(setDateBody);
    setDateEntity->addComponent(setDateMaterial);
    setDateEntity->addComponent(setDateTransform);

    timePortalEntity->addComponent(timePortalBody);
    timePortalEntity->addComponent(timePortalMaterial);
    timePortalEntity->addComponent(timePortalTransform);

    guideMarkerEntity->addComponent(guideMarkerBody);
    guideMarkerEntity->addComponent(guideMarkerMaterial);
    guideMarkerEntity->addComponent(guideMarkerTransform);

    //Setting the parent
    yellowBuoyEntity->setParent(rootEntity);
    blueBuoyEntity->setParent(rootEntity);
    redBuoyEntity->setParent(rootEntity);
    greenBuoyEntity->setParent(rootEntity);
    setDateEntity->setParent(rootEntity);
    timePortalEntity->setParent(rootEntity);
    guideMarkerEntity->setParent(rootEntity);

}
