#ifndef SUBSUB_H
#define SUBSUB_H

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




/**
 * @brief The SubSub class
 * Class for testing sub in simView
 * Sub substituted by cylinder
 * Attempt to achieve basic movement
 *
 * Note: Always use Qt3D::member to call
 * Qt3D members b/c of ambiguity with other
 * Qt modules eg. QTransform and Qt3D::QTransform
 * ambiguity error when using Qt3D namespace
 * b/c Qt namespace is automatic
 *
 *
 */

class SubSub: public QObject
{
    Q_OBJECT

public:
    SubSub();
    void initialize(Qt3D::QEntity *rootEntity);

    /**
     * @param subBody pointer to mesh used to shape sub
     * As a component it can be attached to an entity much like a script is attached
     * to a model in 3D simulation/game environments such as Unity3D
     * in order to modify it's behaviour. This component gives the
     * sub its shape in the 3D world
     *
     * @param subMaterial pointer to material (color) for sub
     *
     * @param subTranslation pointer to the Qt3D::QTranslationTransform
     * which holds the position of the sub's centre in 3D space. This
     * will be modified in order to move the sub. (setTranslation).
     * The immediate position can be received with the Translation()
     * member
     *
     * @param subRotation pointer to the Qt3D::QRotateTransformation
     * which holds the orientation of the sub in 3D about an axis
     * defined by its setAxis(QVector3D) member. This is modified in
     * order to move the sub (setAngleDeg (float)) or setAngleRad.
     * The current value can be retrieved using angleDeg() or angleRad()
     * respectively
     *
     *
     * @param subTransform a Qt3D::QTranform pointer a.k.a. a
     * pointer to the sub's total transform component. This
     * allows the sub its position and the ability to change its
     * position on the fly
     *
     */



    Qt3D::QCylinderMesh *subBody;
    Qt3D::QPhongMaterial *subMaterial;
    Qt3D::QTranslateTransform *subTranslation;
    Qt3D::QRotateTransform *subRoll;
    Qt3D::QRotateTransform *subYaw;
    Qt3D::QRotateTransform *subPitch;
    Qt3D::QTransform *subTransform;

    Qt3D::QCamera *frontCamera;
    Qt3D::QCamera *downCamera;





    float poolDepth;

    void moveTowards(QVector3D targetPosition);
    void moveTowards(float targetx, float targety, float targetz);
    void turnSub (float newYawAngleDegrees);


    /**
     * @param subEntity a pointer to the entity of the sub
     * entity being the concept of the sub which is made real
     * using the components to give it behaviours and shape. The 'soul'
     * to the mind/body that is the components
     *
     * @param keepCameraAttached Slot called when the sub has moved
     * Maintains a constant camera sub offset and creates a new
     * view centre corresponding to the current forward vector
     *
     * @param forward last known forward vector (unit vector)
     *
     * @param downward Points towards the bottom of the pool
     *
     * @param cameraOffset QVector3D sets the cameras in front
     * of the sub
     *
     * @param frontViewCentre offseet QVector3D represent the
     * position (in local coordinates) that the frontcamera should be
     * pointing towards.
     *
     * @param DownViewCentreOffset QVector3D represents the
     * position i(in local coordinates) that the downward
     * camera should be pointing at. Constant since looking at
     * bottom of the pool
     */



public slots:
    //Attempting to addMovement


     void keepCameraAttached();

private:
    Qt3D::QEntity *subEntity;
    QVector3D forward;
    QVector3D downward;
    QVector3D cameraOffset;
    QVector3D frontViewCentreOffset;
    QVector3D DownViewCentreOffset;

   // QTimer *timer;
};

#endif // SUBSUB_H
