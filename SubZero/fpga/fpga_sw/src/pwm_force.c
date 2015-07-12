/*
Create a lookup table and use it to compute a PWM value, given force.

This lookup table is used to speed up math for a non-linear function from force to PWM.
*/

#include "pwm_force.h"
#include "settings.h"

#include <math.h>
#include <stdio.h>

// given a force, this function returns the pwm to generate that force using the equations above
// or the lookup, if necessary.

// declare this array so it can be used on initializing the look-up
#define SIZE 200
int pwm_from_force[SIZE]; // array of pwms

// Inverse function of the cubic, mapping force to PWM
int inverse_cubic(double x){
  //the inverse of the cubic is very ugly in appearance, so it will be broken down into bits.
  //source: http://www.wolframalpha.com/input/?i=find+inverse+of+y+%3D+%281.888e-5%29*x^3+-+%286.593e-6%29*x^2+%2B+%284.320e-3%29*x
  double a = 1.38739*pow(10,9)*sqrt(1.20303*pow(10,19)*pow(x,2)-1.20976*pow(10,16)*x+7.60966*pow(10,15))-4.81213*pow(10,18)*x+2.41952*pow(10,15);
  double b = pow(a,0.33333);
  double term_one = 0.116402 - 0.0000176554*b;
  double term_two = (4.31923*pow(10,6))/b;
  
  double inverse_result = term_one + term_two;
  return (int)(5.12 * inverse_result);
}

void init_lookup() {
  int i;
  for (i = 0; i < SIZE; i++) {
    double force = (i - SIZE/2) / (double) (SIZE/2);
    pwm_from_force[i] = inverse_cubic(force);
  }
}

int pwm_of_force (double force)
{
  if (force > MIN_LINEAR_FORCE) {
    return MIN_LINEAR_PWM + (int)((force - MIN_LINEAR_FORCE) / 0.045 * 5.12);
  }
  if (force < -MIN_LINEAR_FORCE) {
    return -MIN_LINEAR_PWM + (int)((force + MIN_LINEAR_FORCE) / 0.0502 * 5.12);
  }

  int force_index = (int)((force + 1)*SIZE/2);

  return pwm_from_force[force_index];
}
