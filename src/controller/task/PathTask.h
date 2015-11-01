#ifndef PATHTASK_H
#define PATHTASK_H

#include "Task.h"
#include "TurnTask.h"
#include "SpeedTask.h"
#include "CameraModel.h"
#include "LineFilter.h"
#include "ShapeFilter.h"
#include "Logger.h"
#include <unistd.h>

class PathTask : public Task {
public:
    PathTask();
    virtual ~PathTask();
    PathTask(Model* cameraModel, TurnTask* turnTask, SpeedTask* speedTask);

    void execute();

private:
    Logger* logger = new Logger("PathTask");

    CameraModel* cameraModel;
    TurnTask* turnTask;
    SpeedTask* speedTask;

    bool moving;
    bool done;

    float forwardSpeed;

    // distance in pixels considered to be in line with the sub
    float alignThreshold;
    int imgWidth, imgHeight;

    // Helper functions
    void setSpeed(float amount);
    void stop();
    void rotate(float amount);
    void moveTo(cv::Point2f pos);
};

#endif // PATHTASK_H
