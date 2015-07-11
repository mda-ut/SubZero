#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
private:
    int power;
public:
    Motor();
    void setPower(int power);
    int getPower();
};

#endif // MOTOR_H
