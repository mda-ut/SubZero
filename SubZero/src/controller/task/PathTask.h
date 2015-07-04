#ifndef PATHTASK_H
#define PATHTASK_H

#include "Task.h"
#include "CameraState.h"
#include "LineFilter.h"
#include "ShapeFilter.h"

#define PI 3.14159

class PathTask: Task
{
public:
    PathTask();

    void allign(std::vector<std::vector<float>> lines);

    void execute(CameraState* s);
private:
    bool startPath = false;     //first vertical line (start of rect)
    bool finPath = false;       //last vertical line (end of rect)
    bool horzInSight = false;
};

#endif // PATHTASK_H
