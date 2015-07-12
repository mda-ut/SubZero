// Function prototypes implemented in utils.c

#ifndef _MDA_UTILS_H
#define _MDA_UTILS_H

#include "accelerometer_adxl345_spi.h"

enum MOTOR_DIR {
  MOTOR_DIR_STOPPED,
  MOTOR_DIR_BRAKE,
  MOTOR_DIR_FORWARD,
  MOTOR_DIR_REVERSE
};

void init();
void alt_getline(char *, int);
void service_main_loop();
int read_hex(char *);
void print_int(int);
void set_motor_dir(int, enum MOTOR_DIR);
char get_motor_dir(int);
void set_motor_duty_cycle(int, int);
void set_pwm_freq(int);
void set_pow(int);
int get_motor_duty_cycle(int);
int get_pwm_freq();
void get_accel(struct t_accel_data *);
int get_depth();

// API to give commands to NIOS

enum COMMAND_ID {
  COMMAND_INVALID,
  COMMAND_FORWARD,
  COMMAND_REVERSE,
  COMMAND_STOP_ALL,
  COMMAND_STOP,
  COMMAND_BRAKE,
  COMMAND_DUTY_CYCLE,
  COMMAND_FREQ,
  COMMAND_POW,
  COMMAND_ACCEL,
  COMMAND_ACCEL_X,
  COMMAND_ACCEL_Y,
  COMMAND_ACCEL_Z,
  COMMAND_DEPTH,
  COMMAND_MOTORS,
  COMMAND_HELP,
  COMMAND_SPEED,
  COMMAND_HEADING,
  COMMAND_SET_DEPTH,
  COMMAND_CONTROLLER,
  COMMAND_IMU_SHELL,
  COMMAND_PID_DEPTH,
  COMMAND_PID_PITCH,
  COMMAND_PID_ROLL,
  COMMAND_PID_YAW
};

struct command_struct {
  char *name;
  enum COMMAND_ID id;
  char *help_string;
};

#endif
