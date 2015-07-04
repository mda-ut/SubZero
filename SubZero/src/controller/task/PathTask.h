#ifndef PATHTASK_H
#define PATHTASK_H

#include "Task.h"
#include "TurnTask.h"
#include "SpeedTask.h"
#include "CameraModel.h"
#include "LineFilter.h"
#include "ShapeFilter.h"
#include "Logger.h"

class PathTask : public Task {
public:
    PathTask();
    ~PathTask();
    PathTask(CameraModel* cameraModel, TurnTask* turnTask, SpeedTask* speedTask);

    void execute();

private:
    Logger* logger = new Logger("PathTask");

    CameraModel* cameraModel;
    TurnTask* turnTask;
    SpeedTask* speedTask;
    bool startPath;     //first vertical line (start of rect)
    bool finPath;       //last vertical line (end of rect)
    bool horzInSight;
    bool done;
    float inlineThresh;
    int imgWidth, imgHeight;

    void moveTo(cv::Point2f pos);

    bool debug = true;
    void println(std::string s);
};

#endif // PATHTASK_H
