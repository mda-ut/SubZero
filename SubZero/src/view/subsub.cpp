#include  "subsub.h"
#include  <QEntity>
#include  <QTransform>
#include  <QTranslateTransform>
#include  <QRotateTransform>
#include  <QScaleTransform>
#include  <QCylinderMesh>
#include  <QPhongMaterial>

SubSub::SubSub()
{

}

void SubSub::initialize(Qt3D::QEntity *rootEntity)
{
    subBody = new Qt3D::QCylinderMesh;
    subMaterial = new Qt3D::QPhongMaterial;
    subTranslation = new Qt3D::QTranslateTransform;
    subRotation = new Qt3D::QRotateTransform;
    subTransform = new Qt3D::QTransform;
    subEntity = new Qt3D::QEntity;

    //Shape/Mesh Setup
        //Cylinder Meshes require a radius, height(length), rings and slices
        //rings are used to section the cylinder each cylinder requires 2 rings (top and bottom)
        //slices represent the resolution of the cylinder. Think slices of pizza
        //The more slices the greater the resolution. use 20 for a good circular shape
        // 5 gives you a pentagonal prism instead of a proper cylinder, 6 hexagonal etc.
    subBody->setRadius(1.0f);
    subBody->setLength(2.0f);
    subBody->setRings(2);
    subBody->setSlices(20);

    //Material
    subMaterial->setDiffuse(QColor(QRgb(0xbeb32b)) );// Create color from hexidecimal

    //Positioning
    subTranslation->setTranslation( QVector3D(0.0f, 0.0f, 0.0f) );
    subRotation->setAxis( QVector3D(1.0f, 0.0f, 0.0f) ); //Set Axis about which to rotate
    subRotation->setAngleDeg(25.0f);// Rotate this much about the axis of rotation

   //Add the Transforms to the transform component
    subTransform->addTransform(subTranslation);
    subTransform->addTransform(subRotation);

    //Add the components to the entity
    subEntity->addComponent(subBody);
    subEntity->addComponent(subMaterial);
    subEntity->addComponent(subTransform);

    //Allow the sub to be visible by setting a parent
    subEntity->setParent(rootEntity);

}
