#ifndef PORTALTASK_H
#define PORTALTASK_H
#include "Task.h"
#include "CameraModel.h"
#include "ShapeFilter.h"

class PortalTask: public Task
{
public:
    PortalTask(CameraModel* camModel);

    int task();
    void execute();
private:
    CameraModel* camModel;
    Properties* settings;

    float thresh;
    float angleThresh;
    float travelTime;
    float travelDist;

    void rotate(float t);
    void move(float d);
    void rise(float h);
    void slide (float d);
    void println(std::string);

    float calcPixScale(std::vector<cv::RotatedRect> rekts);
};

#endif // PORTALTASK_H
