#ifndef SIMULATEDSUB_H
#define SIMULATEDSUB_H

#include  <QEntity>
#include  <QTransform>
#include  <QTranslateTransform>
#include  <QRotateTransform>
#include  <QScaleTransform>
#include  <QCylinderMesh>
#include  <QPhongMaterial>

class SimulatedSub {
public:
    SimulatedSub();
    SimulatedSub(Qt3D::QEntity* parentEntity);
    ~SimulatedSub();

    void initialize();

private:
    Qt3D::QEntity *subEntity;

    Qt3D::QCylinderMesh *subBody;
    Qt3D::QPhongMaterial *subMaterial;
    Qt3D::QTranslateTransform *subTranslation;
    Qt3D::QRotateTransform *subRotation;
    Qt3D::QTransform *subTransform;

    Qt3D::QEntity* parentEntity;
};

#endif // SIMULATEDSUB_H
