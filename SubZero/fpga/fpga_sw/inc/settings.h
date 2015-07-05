// Set some #define values to use as settings

// allow the user to interact when using commands
#define INTERACTIVE

// constants
#define CLOCK_SPEED 50000000
#define TIMER_RATE_IN_HZ 20
#define NUM_DEPTH_VALUES 64 /* Ensure this is a power of 2 for better performance */

#define NUM_MOTORS 6
#define STR_LEN 127
#define RAD_TO_DEG 57.3  /* 180/PI */
#define MOTOR_CONTROLLER_0_DUTY_CYCLE (MOTOR_CONTROLLER_0_BASE + 32)

#define ZERO_PWM 512
#define FULL_PWM (2*ZERO_PWM)

// Limits
#define PWM_LIMIT_FACTOR 0.8
#define MAX_PWM (PWM_LIMIT_FACTOR * FULL_PWM)
#define MIN_PWM ((1-PWM_LIMIT_FACTOR) * FULL_PWM)

#define FORCE_REDUCTION_FACTOR 0.85

#ifndef INTERACTIVE
#undef puts
#undef printf
#undef putchar
#else
#include <stdio.h>
#endif

/** Ritchie's PID controller settings. 
 * These are multiplicative constants in the PID equation
 * Alpha is the decay rate for Integral term
 */

#define ROLL_CONST_P 18.0
#define ROLL_CONST_I 0.0 /* NOT CALIBRATED */
#define ROLL_CONST_D 0.0 /* NOT CALIBRATED */
#define ROLL_ALPHA 0.0
#define PITCH_CONST_P 24.0
#define PITCH_CONST_I 0.0 /* NOT CALIBRATED */
#define PITCH_CONST_D 0.0 /* NOT CALIBRATED */
#define PITCH_ALPHA 0.0
#define YAW_CONST_P 12.0
#define YAW_CONST_I 0.0 /* NOT CALIBRATED */
#define YAW_CONST_D 0.0 /* NOT CALIBRATED */
#define YAW_ALPHA 0.0
#define DEPTH_CONST_P 10.0
#define DEPTH_CONST_I 0.000
#define DEPTH_CONST_D 1
#define DEPTH_ALPHA 0.0

/** The following constants define the scaling between PID controller outputs
 *  and the motor force. Say the PID reads a string of angles/depth values and spits
 *  out "30". This constant converts this relative control factor to relative motor force.
 *  We should try to keep the force around -100 to 100 or something
 */
#define FACTOR_PID_ROLL_TO_FORCE 1
#define FACTOR_PID_PITCH_TO_FORCE 1
#define FACTOR_PID_YAW_TO_FORCE 1
#define FACTOR_PID_DEPTH_TO_FORCE 1
#define FACTOR_SPEED_TO_FORCE 5

/** This converts the controller force into lbs, so that it can be mapped to a PWM */
#define FACTOR_CONTROLLER_FORCE_TO_LBS 0.005
