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
};

#endif // BUOYTASK_H
