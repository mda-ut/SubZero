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
    /** With respect to front camera
     * +X -> left
     * +Y-> up
     * +Z -> straight (with respect to screen not forwards vector)
     */

    //max depth
    poolDepth = -20.0f;

    //Initial forwards & downwards
    forward = QVector3D(0.0f, 0.0f, 1.0f);
    downward = QVector3D(0.0f, -1.0f, 0.0f);
    cameraOffset = (forward*2);
    frontViewCentreOffset = (forward*30);
    DownViewCentreOffset = (downward*20);


    //Camera Setup
    frontCamera = new Qt3D::QCamera(rootEntity);
    frontCamera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    frontCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));

    downCamera = new Qt3D::QCamera(rootEntity);
    downCamera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    downCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));


    //SubSetup
    subBody = new Qt3D::QCylinderMesh;
    subMaterial = new Qt3D::QPhongMaterial;
    subTranslation = new Qt3D::QTranslateTransform;
    subRoll = new Qt3D::QRotateTransform;
    subYaw = new Qt3D::QRotateTransform;
    subPitch = new Qt3D::QRotateTransform;
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
    subMaterial->setDiffuse(QColor(QRgb(0xbeb32b)) );

    //Initial Positioning w/ respect to origin
    subTranslation->setTranslation( QVector3D(0.0f, 0.0f, 0.0f) );
    subRoll->setAxis( QVector3D(1.0f, 0.0f, 0.0f) ); //Set Roll axis (X)
    subRoll->setAngleDeg(90.0f);

    subRoll->setAxis( QVector3D(0.0f, 1.0f, 0.0f) ); //Set Yaw Axis (Y)
    subRoll->setAngleDeg(0.0f);

    subRoll->setAxis( QVector3D(0.0f, 0.0f, 1.0f) ); //Set Pitch Axis (Z)
    subRoll->setAngleDeg(0.0f);


        //Camera
    frontCamera->setPosition(  (subTranslation->translation() + cameraOffset)  );//Sub Camera offset 2 in direction
    downCamera->setPosition(  (subTranslation->translation() + cameraOffset)  );

        //Camera View Centre appears to end up pointing to
        //what is considered the right side of the screen
        //In global coordingates (need to consider this in movement)
        //This is where the camera is pointed to.
        //Adding a small offset to compensate: offset = <-10,0,60>
    frontCamera->setViewCenter(frontViewCentreOffset);// since sub position is origin
    downCamera->setViewCenter(frontViewCentreOffset);





   //Add the sub Transformations to the transform component
    subTransform->addTransform(subTranslation);
    subTransform->addTransform(subRoll);
    subTransform->addTransform(subYaw);
    subTransform->addTransform(subPitch);

    //Add the components to the entity
    subEntity->addComponent(subBody);
    subEntity->addComponent(subMaterial);
    subEntity->addComponent(subTransform);

    //Allow the sub to be visible by setting a parent
    subEntity->setParent(rootEntity);
}




void SubSub::moveTowards(QVector3D targetPosition)
{
    //Don't go below bottom of the pool
    if (targetPosition.y() < poolDepth)
    {
        targetPosition.setY(poolDepth);
    }


    //Update forward
    forward = targetPosition -subTranslation->translation();
    forward = forward.normalized();
    cameraOffset = forward*2;
    frontViewCentreOffset = (forward * 30);


    //Move to the newPosition
    subTranslation->setTranslation(targetPosition);


    //Add emit for slot keepCameraAttached
}



void SubSub::moveTowards(float targetx, float targety, float targetz)
{
  QVector3D targetPosition = QVector3D(targetx, targety, targetz);

  moveTowards(targetPosition);
}



void SubSub::turnSub(float newYawAngleDegrees)
{

    float deltaYawDeg = (newYawAngleDegrees - subYaw->angleDeg() );
    subYaw->setAngleDeg(newYawAngleDegrees);
    frontCamera->rotate( QQuaternion::fromAxisAndAngle( subYaw->axis(), deltaYawDeg) );
}




void SubSub::keepCameraAttached()
{

    QVector3D newCameraPosition = subTranslation->translation() + cameraOffset;

    frontCamera->setPosition(newCameraPosition);
    downCamera->setPosition(newCameraPosition);

    //Fix view centre based on forward

    QVector3D newfrontViewCentre = (subTranslation->translation() + frontViewCentreOffset);
    frontCamera->setViewCenter(newfrontViewCentre);


}
