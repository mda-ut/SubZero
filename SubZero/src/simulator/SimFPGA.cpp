#include "SimFPGA.h"
#include "Timer.h"

#include <unistd.h>

/** =========================================================
 *  CONSTRUCTOR AND DESTRUCTOR
 *  =========================================================
 */


SimFPGA::SimFPGA(Properties* properties) {
    power = false;
    motors = false;
    position.x = std::stod(properties->getProperty("SIMSUB_START_X"));
    position.y = std::stod(properties->getProperty("SIMSUB_START_Y"));
    position.z = std::stod(properties->getProperty("SIMSUB_START_Z"));
    yaw = std::stod(properties->getProperty("SIMSUB_START_YAW"));
    speed = 0;
    depth_speed = 0;
    angular_speed = 0;
    accel = 0;
    depth_accel = 0;
    angular_accel = 0;
    target_depth = 0;
    target_yaw = 0;
    target_speed = 0;
    update_period = 1 / std::stod(properties->getProperty("SIMSUB_UPDATE_FREQ"));
    executing = true;
    updateThread = std::thread(&SimFPGA::updateLoop,this);
}

SimFPGA::~SimFPGA() {
    executing = false;
    updateThread.join();
    power_off();
}

void SimFPGA::updateLoop() {
    double timeElapsed;
    Timer timer;
    timer.start();
    while(executing) {
        timeElapsed = timer.getTimeElapsed();
        if (timeElapsed > update_period) {
            timer.start();
            if(power && motors) {
                update(timeElapsed);
            }
        }
        std::this_thread::yield();
    }
}

//calculates new data based on a constant acceleration
void SimFPGA::update(double period) {
    //update position
    double distance_traveled =  (0.5 * accel * period * period) + (speed * period);
    position.x += cos(yaw * M_PI/180) * distance_traveled;
    position.y += sin(yaw * M_PI/180) * distance_traveled;
    position.z += (0.5 * depth_accel * period * period) + (depth_speed * period);
    yaw += (0.5 * angular_accel * period * period) + (angular_speed * period);

    if (yaw >= 180) {
        yaw -= 360;
    } else if (yaw < -180) {
        yaw += 360;
    }

    // update speed
    speed += (accel * period) - (speed );
    depth_speed += (depth_accel * period) - (depth_speed );
    angular_speed += (angular_accel * period) - (angular_speed );

    //update acceleration
    if (speed < target_speed) {
        accel = ACCEL;
    } else if (speed > target_speed) {
        accel = -ACCEL;
    } else {
        accel = 0;
    }
/*
    if (position.z < (target_depth)) {
        depth_accel = DEPTH_ACCEL;
    } else if (position.z > (target_depth)){
        depth_accel = -DEPTH_ACCEL;
    } else {
        depth_accel = 0;
    }
*/
    depth_accel = pid_depth.getPIDValue(target_depth - position.z, period);


    //handle across the 180/-180 border
    double yaw_diff = target_yaw - yaw;
    /*if ((yaw_diff > 0 && yaw_diff <= 180) || (yaw_diff > -360 && yaw_diff <= -180)) {
        angular_accel = ANGULAR_ACCEL;
    } else if ((yaw_diff < 0 && yaw_diff >= -180) || (yaw_diff < 360 && yaw_diff >= 180)){
        angular_accel = -ANGULAR_ACCEL;
    } else {
        angular_accel = 0;
    }*/
    if (yaw_diff > 180) {
        yaw_diff -= 360;
    } else if (yaw_diff <= -180) {
        yaw_diff += 360;
    }
    //logger->trace("yaw_diff = " + std::to_string(yaw_diff));
    angular_accel = pid_yaw.getPIDValue(yaw_diff, period);
    //TODO call code to update simulator engine's sub's position and yaw
    logger->info("yaw: " + std::to_string(yaw));
}


void SimFPGA::power_on() {
    power = true;
}

void SimFPGA::power_off() {
    motors = false;
    power = false;
    accel = 0;
    depth_accel = 0;
    angular_accel = 0;
}

int SimFPGA::get_power() {
    return power;
}

void SimFPGA::startup_sequence() {
    target_depth = position.z;
    target_yaw = yaw;
    target_speed = 0;
    motors = true;
}

void SimFPGA::set_target_speed(int targetSpeed) {
    target_speed = targetSpeed;
}

void SimFPGA::set_target_depth(int targetDepth) {
    target_depth = -targetDepth; //simulator and software do depth differently
}

void SimFPGA::set_target_yaw(int targetYaw) {
    target_yaw = -targetYaw;
    logger->trace("yaw set to: " + std::to_string(target_yaw));
}

int SimFPGA::get_yaw() {
    return (int)(-1*yaw);
}

int SimFPGA::get_depth() {
    return (int)(-1*position.z);
}

void SimFPGA::set_pid_depth(double P, double I, double D, double alpha) {
    pid_depth.setPIDConstants(P, 0, 0);
}

void SimFPGA::set_pid_yaw(double P, double I, double D, double alpha) {
    pid_yaw.setPIDConstants(P, 0, 0);
}





