#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <vector>
#include <string.h>

#include "Motor.h"


/*
 * Direction enumeration
 */
enum {
    FWD,
    HOR,
    VER,
    X,Y,Z
};

class Submarine
{
private:
    std::vector<Motor> motors;
public:

    /** =========================================================
     *  CONSTRUCTOR AND DESTRUCTOR
     *  =========================================================
     */

    /**
     * @brief Submarine constructor
     */
    Submarine();

    /**
     * @brief ~Submarine destructor
     */
    virtual ~Submarine();

    /** =========================================================
     *  MOTORS
     *  =========================================================
     */
    int getMotorPower(int id=-1);
    int getMotorDir(int id=-1);
};

#endif // SUBMARINE_H
