#include "Motor.h"

Motor::Motor()
{
    this->power = 0;
}

void Motor::setPower(int power)
{
    this->power = power;
}

int Motor::getPower()
{
    return this->power;
}
