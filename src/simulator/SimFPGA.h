#ifndef SimFPGA_H
#define SimFPGA_H

#include <thread>
#include <queue>
#include <string>
#include <queue>
#include <cmath>
//#include "subsub.h"

#include "Properties.h"
#include "Logger.h"
#include "PIDController.h"
#include "SimulatedSub.h"

typedef struct {
    double x;
    double y;
    double z;
} sim_position;

#define ACCEL 5
#define DEPTH_ACCEL 5
#define ANGULAR_ACCEL 3

#define FWD_LOSS_CONST 0.2
#define DEPTH_LOSS_CONST 0.2
#define ANG_LOSS_CONST 0.5

class SimFPGA {
private:

    /** =========================================================
     *  MEMBERS
     *  =========================================================
     */

    /*
     * Thread for the read function to continue updating simulated submarine state.
     */
    std::thread updateThread;

    Logger* logger = new Logger("SimFPGA");

    SimulatedSub* simSub;
    bool executing;
    bool power, motors;
    sim_position position;
    double yaw;
    double speed, depth_speed, angular_speed;
    double accel, depth_accel, angular_accel; //accel in m/s^2
    int target_depth;
    int target_yaw;
    int target_speed;
    double update_period;
    PIDController pid_depth, pid_yaw;


    void updateLoop();

    /**
     * @brief update Calculates mock data based on a constant acceleration
     * @param period
     */
    void update(double period);


public:

    /** =========================================================
     *  CONSTRUCTOR AND DESTRUCTOR
     *  =========================================================
     */

    /**
     * @brief SimFPGA constructor
     */
    SimFPGA(Properties* properties, SimulatedSub* simSub);

    /**
     * @brief ~SimFPGA destructor
     */
    virtual ~SimFPGA();

    /** =========================================================
     *  INTERFACE METHODS
     *  =========================================================
     */

    void power_on();
    void startup_sequence();
    void power_off();
    int get_power();

    void set_target_speed(int);
    void set_target_depth(int);
    void set_target_yaw(int);

    int get_yaw();
    int get_depth();

    void set_pid_depth(double, double, double, double);
    void set_pid_yaw(double, double, double, double);

};

#endif // SimFPGA_H
