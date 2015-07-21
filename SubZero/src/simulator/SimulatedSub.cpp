#include "SimulatedSub.h"

SimulatedSub::SimulatedSub() {

}

SimulatedSub::SimulatedSub(Qt3D::QEntity* parentEntity) {
    this->parentEntity = parentEntity;
}

SimulatedSub::~SimulatedSub() {

}

void SimulatedSub::initialize() {
    //max depth
    poolDepth = -20.0f;

    //Initial forwards & downwards
    forward = QVector3D(0.0f, 0.0f, 1.0f);
    downward = QVector3D(0.0f, -1.0f, 0.0f);
    cameraOffset = (forward*2);
    frontViewCentreOffset = (forward*30);
    DownViewCentreOffset = (downward*20);

    //Camera Setup
    frontCamera = new Qt3D::QCamera(parentEntity);
    frontCamera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    frontCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));

    downCamera = new Qt3D::QCamera(parentEntity);
    downCamera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    downCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));

    //SubSetup
    subBody = new Qt3D::QCylinderMesh();
    subMaterial = new Qt3D::QPhongMaterial();
    subTranslation = new Qt3D::QTranslateTransform();
    subRoll = new Qt3D::QRotateTransform();
    subYaw= new Qt3D::QRotateTransform();
    subPitch = new Qt3D::QRotateTransform();
    subTransform = new Qt3D::QTransform();
    subEntity = new Qt3D::QEntity();

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
    subTranslation->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    subPitch->setAxis(QVector3D(1.0f, 0.0f, 0.0f)); //Set Pitch Axis (X)
    subPitch->setAngleDeg(90.0f);

    subRoll->setAxis( QVector3D(0.0f, 1.0f, 0.0f) ); //Set Roll Axis (Y)
    subRoll->setAngleDeg(0.0f);

    subYaw->setAxis( QVector3D(0.0f, 0.0f, 1.0f) ); //Set Yaw Axis (Z)
    subYaw->setAngleDeg(0.0f);

    //Add the Transforms to the transform component
    subTransform->addTransform(subTranslation);
    subTransform->addTransform(subRoll);
    subTransform->addTransform(subYaw);
    subTransform->addTransform(subPitch);

    //Add the components to the entity
    subEntity->addComponent(subBody);
    subEntity->addComponent(subMaterial);
    subEntity->addComponent(subTransform);

    //Allow the sub to be visible by setting a parent
    subEntity->setParent(parentEntity);
}

void SimulatedSub::moveTowards(QVector3D targetPosition)
{
    //Don't go below bottom of the pool
    if (targetPosition.z() < poolDepth)
    {
        targetPosition.setZ(poolDepth);
    }


    //Update forward
    forward = targetPosition - subTranslation->translation();
    forward = forward.normalized();
    cameraOffset = forward*2;
    frontViewCentreOffset = (forward * 30);


    //Move to the newPosition
    subTranslation->setTranslation(targetPosition);


    //Add emit for slot keepCameraAttached
    emit keepCameraAttached();
}



void SimulatedSub::moveTowards(float targetx, float targety, float targetz)
{
  QVector3D targetPosition = QVector3D(targetx, targety, targetz);

  moveTowards(targetPosition);
}



void SimulatedSub::turnSub(float newYawAngleDegrees)
{

    float deltaYawDeg = (newYawAngleDegrees - subYaw->angleDeg() );
    subYaw->setAngleDeg(newYawAngleDegrees);
    frontCamera->rotate( QQuaternion::fromAxisAndAngle( subYaw->axis(), deltaYawDeg) );
}




void SimulatedSub::keepCameraAttached()
{

    QVector3D newCameraPosition = subTranslation->translation() + cameraOffset;

    frontCamera->setPosition(newCameraPosition);
    downCamera->setPosition(newCameraPosition);

    //Fix view centre based on forward

    QVector3D newfrontViewCentre = (subTranslation->translation() + frontViewCentreOffset);
    frontCamera->setViewCenter(newfrontViewCentre);

}

