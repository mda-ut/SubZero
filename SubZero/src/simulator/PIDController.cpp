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
    // Update the cumulative error over time
    cumulativeError += error * elapsedTime;
    // Calculate each term
    double pTerm = P * error;
    double iTerm = I * cumulativeError;
    double dTerm = (D * (error - previousError)) / elapsedTime;
    logger->trace("P term: " + std::to_string(pTerm));
    logger->trace("I term: " + std::to_string(iTerm));
    logger->trace("D term: " + std::to_string(dTerm));
    double PID = pTerm + iTerm + dTerm;
    // Store new error as previous error for next iteration
    previousError = error;
    return PID;
}

