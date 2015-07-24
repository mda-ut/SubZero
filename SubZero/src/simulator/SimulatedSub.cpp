#include "SimulatedSub.h"

SimulatedSub::SimulatedSub() {

}

SimulatedSub::SimulatedSub(Qt3D::QEntity* parentEntity) {
    this->parentEntity = parentEntity;
}

SimulatedSub::~SimulatedSub() {
    delete subEntity;
    logger->info("Deleted");
    delete logger;
}

void SimulatedSub::initialize() {
    //max depth
    poolDepth = -20.0f;

    //Initial forwards & downwards
    forward = QVector3D(0.0f, 0.0f, 1.0f);
    downward = QVector3D(0.0f, -1.0f, 0.0f);
    frontCameraOffset = (forward*0.5);
    downCameraOffset = downward*0.5;
    frontViewCentreOffset = (forward*4);
    downViewCentreOffset = (downward*4);

    //Camera Setup
    frontCamera = new Qt3D::QCamera(parentEntity);
    frontCamera->lens()->setPerspectiveProjection(45.0f, 4.0f/3.0f, 0.1f, 1000.0f);
    frontCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));


    downCamera = new Qt3D::QCamera(parentEntity);
    downCamera->lens()->setPerspectiveProjection(45.0f, 4.0f/3.0f, 0.1f, 1000.0f);
    downCamera->setUpVector(QVector3D(0.0f, 0.0f, 1.0f));


    //SubSetup
    subBody = new Qt3D::QCylinderMesh();
    subMaterial = new Qt3D::QPhongMaterial();
    subTranslation = new Qt3D::QTranslateTransform();
    subRoll = new Qt3D::QRotateTransform();
    subYaw = new Qt3D::QRotateTransform();
    subPitch = new Qt3D::QRotateTransform();
    subTransform = new Qt3D::QTransform();
    subEntity = new Qt3D::QEntity();

    //Shape/Mesh Setup
    //Cylinder Meshes require a radius, height(length), rings and slices
    //rings are used to section the cylinder each cylinder requires 2 rings (top and bottom)
    //slices represent the resolution of the cylinder. Think slices of pizza
    //The more slices the greater the resolution. use 20 for a good circular shape
    // 5 gives you a pentagonal prism instead of a proper cylinder, 6 hexagonal etc.
    subBody->setRadius(0.3f);
    subBody->setLength(1.0f);
    subBody->setRings(2);
    subBody->setSlices(20);

    //Material
    subMaterial->setAmbient(QColor(QRgb(0xbeb32b)) );// Create color from hexidecimal

    //Positioning
    subTranslation->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    subPitch->setAxis(QVector3D(1.0f, 0.0f, 0.0f)); //Set Pitch Axis (X)
    subPitch->setAngleDeg(0.0f);

    subYaw->setAxis( QVector3D(0.0f, 1.0f, 0.0f) ); //Set Yaw Axis (Y)
    subYaw->setAngleDeg(0.0f);

    subRoll->setAxis( QVector3D(0.0f, 0.0f, 1.0f) ); //Set Roll Axis (Z)
    subRoll->setAngleDeg(0.0f);

    frontCamera->setPosition((subTranslation->translation() + frontCameraOffset));
    downCamera->setPosition((subTranslation->translation() + downCameraOffset));

    frontCamera->setViewCenter(frontViewCentreOffset);
    downCamera->setViewCenter(downViewCentreOffset);

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

    logger->info("Initialized");
}

void SimulatedSub::moveTowards(QVector3D targetPosition) {
    //Don't go below bottom of the pool
    /*if (targetPosition.y() < poolDepth) {
        targetPosition.setY(poolDepth);
    }*/

    // Move to the target position
    subTranslation->setTranslation(targetPosition);
    // Add emit for slot keepCameraAttached
    emit keepCameraAttached();
}



void SimulatedSub::moveTowards(float targetx, float targety, float targetz) {
    QVector3D targetPosition = QVector3D(targetx, targety, targetz);
    logger->debug("Moving to position: " + std::to_string(targetx) + ", " + std::to_string(targety) + ", " + std::to_string(targetz));
    moveTowards(targetPosition);
}



void SimulatedSub::turnSub(float newYawAngleDegrees) {
    //Update forward
    forward = QVector3D(sin(newYawAngleDegrees * M_PI / 180), 0, cos(newYawAngleDegrees * M_PI / 180));
    forward = forward.normalized();
    frontCameraOffset = forward * 0.5;
    frontViewCentreOffset = forward * 4;
    downCamera->setUpVector(forward);

    float deltaYawDeg = (newYawAngleDegrees - subYaw->angleDeg());
    subYaw->setAngleDeg(newYawAngleDegrees);
    frontCamera->rotate( QQuaternion::fromAxisAndAngle( subYaw->axis(), deltaYawDeg) );
    downCamera->rotate( QQuaternion::fromAxisAndAngle( subYaw->axis(), deltaYawDeg) );
    logger->debug("Turning to " + std::to_string(newYawAngleDegrees) + " degrees");
}




void SimulatedSub::keepCameraAttached() {

    frontCamera->setPosition((subTranslation->translation() + frontCameraOffset));
    downCamera->setPosition((subTranslation->translation() + downCameraOffset));

    //Fix view centre based on forward
    QVector3D newfrontViewCentre = (subTranslation->translation() + frontViewCentreOffset);
    frontCamera->setViewCenter(newfrontViewCentre);
    QVector3D newdownViewCentre = (subTranslation->translation() + downViewCentreOffset);
    downCamera->setViewCenter(newdownViewCentre);

}

