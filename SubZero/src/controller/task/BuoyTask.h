#ifndef BUOYTASK_H
#define BUOYTASK_H
#include "Task.h"
#include "CameraModel.h"
#include "ShapeFilter.h"

class BuoyTask: public Task
{
public:
    BuoyTask(CameraModel* camModel);

    int task();
    void execute();

private:
    CameraModel* camModel;
    Properties* settings;
    int imgWidth = -1;
    int imgHeight = -1;
    int travelDist;
    float deltaAngle = -1;

    void move(float d);
    void rise(float h);
    void rotate(float t);
    void slide(float d);
    float calcDistance(float rad);
};
#endif // BUOYTASK_H
