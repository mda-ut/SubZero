#ifndef BUOYTASK_H
#define BUOYTASK_H
#include "Task.h"
#include "TurnTask.h"
#include "SpeedTask.h"
#include "DepthTask.h"
#include "CameraModel.h"
#include "ShapeFilter.h"
#include <unistd.h>

class BuoyTask: public Task
{
public:
    BuoyTask(Model* camModel, TurnTask* tk, SpeedTask* st, DepthTask* dt);
    virtual ~BuoyTask();

    void execute();

private:    
    Logger* logger = new Logger("BuoyTask");
    void println(std::string s);

    CameraModel* camModel;
    TurnTask* tk;
    SpeedTask* st;
    DepthTask* dt;
    Properties* settings;
    int imgWidth = -1;
    int imgHeight = -1;
    int travelDist;
    float deltaAngle = -1;
    bool moveWithSpeed = true;
    int moveSpeed;

    void move(float d);
    void changeDepth(float h);
    void rotate(float angle);
    void slide(float d);
    float calcDistance(float rad);
};
#endif // BUOYTASK_H
