#ifndef _PWM_FORCE_H_
#define _PWM_FORCE_H_

// This aims to implement motor linearization for the motors of the sub.
// What this does is given a force to be applied, it would calculate the 
// pwm necessary to balance the sub (2 back motors each equal 1/2 a front motor)
// given by the equations from the data.

// The ranges given by PWM < -30 and PWM > 30 are linear, so 
// the two linear equations will be used.
// The rest of the values outside that range will be used by the cubic equation 
// that most accurately reflects the data within that range.

void init_lookup();
int pwm_of_force(double force);

// Constants used
#define MIN_LINEAR_FORCE 0.63
#define MIN_LINEAR_PWM (30*5.12)

#endif
