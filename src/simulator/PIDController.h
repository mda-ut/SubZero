#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H
#include "Logger.h"

class PIDController {
private:
    Logger* logger = new Logger("PIDController");

    double P, I, D;
    double previousError;
    double cumulativeError;
public:
    PIDController();
    PIDController(double P, double I, double D);
    ~PIDController();
    void setPIDConstants(double P, double I, double D);
    double getPIDValue(double error, double elapsedTime);
};

#endif // PIDCONTROLLER_H
