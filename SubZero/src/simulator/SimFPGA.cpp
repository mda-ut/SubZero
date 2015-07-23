#include "SimFPGA.h"
#include "Timer.h"

#include <unistd.h>

/** =========================================================
 *  CONSTRUCTOR AND DESTRUCTOR
 *  =========================================================
 */


SimFPGA::SimFPGA(Properties* properties, SimulatedSub* simSub) {
    this->simSub = simSub;
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
    logger->trace("Setting fpga update period to " + std::to_string(update_period));
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

void SimFPGA::update(double period) {
    double target_depth_speed = pid_depth.getPIDValue(target_depth - position.z, period);
    depth_accel = target_depth_speed - depth_speed;
    logger->debug("Depth acceleration: " + std::to_string(depth_accel));

    // Handle across the 180/-180 border
    double yaw_diff = target_yaw - yaw;
    if (yaw_diff > 180) {
        yaw_diff -= 360;
    } else if (yaw_diff <= -180) {
        yaw_diff += 360;
    }
    logger->debug("Yaw difference is " + std::to_string(yaw_diff));
    double target_angular_speed = pid_yaw.getPIDValue(yaw_diff, period);
    angular_accel = target_angular_speed - angular_speed;
    logger->debug("Angular acceleration: " + std::to_string(angular_accel));


    // Update position
    double distance_traveled = (speed * period);
    position.x += cos(yaw * M_PI/180) * distance_traveled;
    position.y += sin(yaw * M_PI/180) * distance_traveled;
    position.z += (0.5 * depth_accel * period * period) + (depth_speed * period);
    yaw += (0.5 * angular_accel * period * period) + (angular_speed * period);


    if (yaw >= 180) {
        yaw -= 360;
    } else if (yaw < -180) {
        yaw += 360;
    }
    // Update speed
    //Currently physics is pretty off but it produces a nice waveform that sorta follows what the sub should do
    speed = target_speed;
    logger->debug("Speed: " + std::to_string(speed));
    depth_speed += (depth_accel * period);
    logger->debug("Depth speed: " + std::to_string(depth_speed));
    angular_speed += (angular_accel * period);
    logger->debug("Angular speed: " + std::to_string(angular_speed));

    //TODO: Call code to update simulator engine's sub's position and yaw
    simSub->moveTowards(position.y/100, position.z/100, position.x/100);    // Conversion between simulator axes and interface axes
    simSub->turnSub(yaw);
}


void SimFPGA::power_on() {
    power = true;
    logger->info("Power ON");
}

void SimFPGA::power_off() {
    motors = false;
    power = false;
    accel = 0;
    depth_accel = 0;
    angular_accel = 0;
    logger->info("Power OFF");
}

int SimFPGA::get_power() {
    return power;
}

void SimFPGA::startup_sequence() {
    target_depth = position.z;
    target_yaw = yaw;
    target_speed = 0;
    motors = true;
    logger->info("Motor startup sequence done");
}

void SimFPGA::set_target_speed(int targetSpeed) {
    target_speed = targetSpeed;
    logger->info("Target speed set to " + std::to_string(targetSpeed));
}

void SimFPGA::set_target_depth(int targetDepth) {
    target_depth = -targetDepth;    // Simulator and software do depth differently
    logger->info("Target depth set to " + std::to_string(targetDepth));
}

void SimFPGA::set_target_yaw(int targetYaw) {
    target_yaw = -targetYaw;
    logger->info("Target yaw set to " + std::to_string(target_yaw));
}

int SimFPGA::get_yaw() {
    return (int)(-1 * yaw);
}

int SimFPGA::get_depth() {
    return (int)(-1 * position.z);
}

void SimFPGA::set_pid_depth(double P, double I, double D, double alpha) {
    pid_depth.setPIDConstants(P, I, D);
}

void SimFPGA::set_pid_yaw(double P, double I, double D, double alpha) {
    pid_yaw.setPIDConstants(P, I, D);
}





