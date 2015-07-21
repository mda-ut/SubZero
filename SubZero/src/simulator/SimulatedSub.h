#ifndef SIMULATEDSUB_H
#define SIMULATEDSUB_H

#include  <QEntity>
#include  <QTransform>
#include  <QTranslateTransform>
#include  <QRotateTransform>
#include  <QScaleTransform>
#include  <QCylinderMesh>
#include  <QPhongMaterial>

//Camera Control
#include <QCamera>
#include <QQuaternion>

//Movement Slots
#include <QTimer>
#include <QObject>

class SimulatedSub : public QObject {
    Q_OBJECT

public:
    SimulatedSub();
    SimulatedSub(Qt3D::QEntity* parentEntity);
    ~SimulatedSub();

    Qt3D::QCamera *frontCamera;
    Qt3D::QCamera *downCamera;

    void moveTowards(QVector3D targetPosition);
    void moveTowards(float targetx, float targety, float targetz);
    void turnSub (float newYawAngleDegrees);

    void initialize();

public slots:
    //Attempting to addMovement


     void keepCameraAttached();

private:
    Qt3D::QEntity *subEntity;

    Qt3D::QCylinderMesh *subBody;
    Qt3D::QPhongMaterial *subMaterial;
    Qt3D::QTranslateTransform *subTranslation;
    Qt3D::QRotateTransform* subRoll;
    Qt3D::QRotateTransform* subPitch;
    Qt3D::QRotateTransform* subYaw;
    Qt3D::QTransform *subTransform;

    float poolDepth;

    QVector3D forward;
    QVector3D downward;
    QVector3D cameraOffset;
    QVector3D frontViewCentreOffset;
    QVector3D DownViewCentreOffset;

    Qt3D::QEntity* parentEntity;
};

#endif // SIMULATEDSUB_H
