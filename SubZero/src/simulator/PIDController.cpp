#include "PIDController.h"

PIDController::PIDController() {
    P = 0;
    I = 0;
    D = 0;
    previousError = 0;
    cumulativeError = 0;
}

PIDController::PIDController(double P, double I, double D) {
    this->P = P;
    this->I = I;
    this->D = D;
    previousError = 0;
    cumulativeError = 0;
}

PIDController::~PIDController() {
    delete logger;
}

void PIDController::setPIDConstants(double P, double I, double D) {
    this->P = P;
    this->I = I;
    this->D = D;
    previousError = 0;
    cumulativeError = 0;
}

double PIDController::getPIDValue(double error, double elapsedTime) {
    cumulativeError += error * elapsedTime;
    double PID = P*error + I*cumulativeError + D*(error-previousError)/elapsedTime;
    previousError = error;
    return PID;
}

