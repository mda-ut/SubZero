/*
 * main.c
 *
 * This is an oversized main file, which includes the main() function.
 * The bulk of this file defines a list of commands and implements how each command is implemented. These commands are the only way
 * to communicate to the FPGA hardware from outside the FPGA. This communication is done through stdin and stdout.
 *
 * The main() function runs init(), then processes commands in a loop. It should never exit.
 *
 * Author: victor
 */

#include <string.h>
#include "altera_avalon_timer_regs.h"
#include "system.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"

#include "controller.h"
#include "interrupts.h"
#include "rs232.h"
#include "settings.h"
#include "utils.h"

// This is the list of all the commands
// Note: end the first string with a \n to ensure an exact match if no arguments are used
struct command_struct my_cmds[] = {
  {"ga\n", COMMAND_ACCEL, "ga - get attitude\n  Usage: ga\n\n  Print acceleration, yaw, pitch and roll\n"},
  {"gax\n", COMMAND_ACCEL_X, "gax - get x-acceleration\n  Usage: gax\n\n  Print x-acceleration\n"},
  {"gay\n", COMMAND_ACCEL_Y, "gay - get y-acceleration\n  Usage: gay\n\n  Print y-acceleration\n"},
  {"gaz\n", COMMAND_ACCEL_Z, "gaz - get z-acceleration\n  Usage: gaz\n\n  Print z-acceleration\n"},
  {"gd\n", COMMAND_DEPTH, "gd - get depth\n  Usage: gd\n\n  Print depth (not converted)\n"},
  {"gm\n", COMMAND_MOTORS, "gm - get motor data\n  Usage: gm\n\n  Print all motor settings (direction on one line and duty cycle on the next)\n"},
  {"h", COMMAND_HELP, "h - help\n  Usage: h <cmd>\n\n  Print the help message for all commands that start with cmd, leave empty to print all help messages\n"},
  {"imu\n", COMMAND_IMU_SHELL, "imu - enter IMU shell\n  Usage: imu\n\n  Enters a shell where stdin goes to the IMU\n  Type quit to exit the IMU shell\n"},
  {"p", COMMAND_POW, "p - power off/on\n  Usage: p (0|1)\n\n  Turn off/on power to all the voltage rails\n"},
  {"sc", COMMAND_CONTROLLER, "sc - set controller off/on\n  Usage: sc (0|1)\n\n  Turn off/on controller\n"},
  {"sd", COMMAND_SET_DEPTH, "sd - set depth of submarine\n"},
  {"sh", COMMAND_HEADING, "sh - set heading of motor positive or negative\n"},
  {"smb", COMMAND_BRAKE, "smb - set motor brake\n  Usage: smb <n>\n\n  Turn the nth motor off\n"},
  {"smd", COMMAND_DUTY_CYCLE, "smd - set motor duty cycle\n  Usage: smd <n> <0xdc>\n\n  Set the duty cycle of the nth motor to dc\nNote: the duty cycle is inputted in hex out of 0x3ff (1024 in decimal)\n"},
  {"smf", COMMAND_FORWARD, "smf - set motor forward\n  Usage: smf <n>\n\n  Turn on the nth motor in the forward direction\n"},
  {"smr", COMMAND_REVERSE, "smr - set motor reverse\n  Usage: smr <n>\n\n  Turn on the nth motor in the reverse direction\n"},
  {"sms", COMMAND_STOP, "sms - set motor stop\n  Usage: sms <n>\n\n  Turn the nth motor off\n"},
  {"spcd", COMMAND_PID_DEPTH, "spcd - set PID constants for depth\n  Usage: spcd P I D Alpha (all in double)\n\n"},
  {"spcp", COMMAND_PID_PITCH, "spcp - set PID constants for pitch\n  Usage: spcd P I D Alpha (all in double)\n\n"},
  {"spcr", COMMAND_PID_ROLL, "spcr - set PID constants for roll\n  Usage: spcd P I D Alpha (all in double)\n\n"},
  {"spcy", COMMAND_PID_YAW, "spcy - set PID constants for yaw\n  Usage: spcd P I D Alpha (all in double)\n\n"},
  {"spf", COMMAND_FREQ, "spf - set PWM frequency\n  Usage: spf <0xn>\n\n  Set the PWM frequency to n in kilohertz\nNote: the frequency is inputted in hex\n"},
  {"ss", COMMAND_SPEED, "ss - set forward or backward speed of motor positive or negative\n"},
  {"stop\n", COMMAND_STOP_ALL, "stop\n  Usage: stop\n\n  Stop all motors\n"},
};

// the size of the above array
const int cmd_len = sizeof(my_cmds) / sizeof(struct command_struct);

// print a description of all available commands
void print_help(char *st)
{
  // ignore leading spaces
  while (*st == ' ') st++;

  printf("Command descriptions:\n\n");

  // -1 to ignore the \n at the end of st
  int len = strlen(st) - 1, i;
  if (len < 0) len = 0;

  for (i = 0; i < cmd_len; i++) {
    if (strncmp(st, my_cmds[i].name, len) == 0) {
      printf("%s\n", my_cmds[i].help_string);
    }
  }
}

// process a command
void process_command(char *st)
{
  // linearly search for the command from the table of commands
  enum COMMAND_ID cid = COMMAND_INVALID;
  int i;
  for (i = 0; i < cmd_len; i++) {
    if (strncmp(st, my_cmds[i].name, strlen(my_cmds[i].name)) == 0) {
      cid = my_cmds[i].id;
      st += strlen(my_cmds[i].name);
      break;
    }
  }

  // variables used in case statement
  struct t_accel_data accel_data;
  struct orientation orientation;
  int c, dc;
  const int ALL = 10; // 10 is 'a' in hex
  double P, I, D, Alpha;

  switch (cid) {
    case COMMAND_INVALID:
      printf("Sorry, command %s is not recognized. For a list of valid commands, type 'h' for help\n", st);
      break;
    case COMMAND_HELP:
      print_help(st+1);
      break;
    case COMMAND_POW:
      i = read_hex(st);
      // When changing power, also stop all motors
      for (c = 0; c < NUM_MOTORS; c++) {
        set_motor_dir(c, MOTOR_DIR_STOPPED);
      }
      set_pow(i);
      printf("setting power %s\n", (i % 2  == 0) ? "off" : "on");
      break;
    case COMMAND_STOP_ALL:
      // Set speed and heading to neutral
      set_target_speed(0);
      set_target_heading(0);
      // When the stop all command is received, maintain the current depth
      set_target_depth(get_depth());
      printf("stopping\n");
      break;
    case COMMAND_STOP:
      i = read_hex(st);
      if (i == ALL) {
        for (c = 0; c < NUM_MOTORS; c++) {
          set_motor_dir(c, MOTOR_DIR_STOPPED);
          printf("stopping motor %d\n", c);
        }
      } else if (i < 0 || i >= NUM_MOTORS) {
        printf("motor # invalid\n");
      } else {
        set_motor_dir(i, MOTOR_DIR_STOPPED);
        printf("stopping motor %d\n", i);
      }
      break;
    case COMMAND_BRAKE:
      i = read_hex(st);
      if (i == ALL) {
        for (c = 0; c < NUM_MOTORS; c++) {
          set_motor_dir(c, MOTOR_DIR_BRAKE);
          printf("braking motor %d\n", c);
        }
      } else if (i < 0 || i >= NUM_MOTORS) {
        printf("motor # invalid\n");
      } else {
        set_motor_dir(i, MOTOR_DIR_BRAKE);
        printf("braking motor %d\n", i);
      }
      break;
    case COMMAND_FORWARD:
      i = read_hex(st);
      if (i == ALL) {
        for (c = 0; c < NUM_MOTORS; c++) {
          set_motor_dir(c, MOTOR_DIR_FORWARD);
          printf("setting motor %d to forward\n", c);
        }
      } else if (i < 0 || i >= NUM_MOTORS) {
        printf("motor # invalid\n");
      } else {
        set_motor_dir(i, MOTOR_DIR_FORWARD);
        printf("setting motor %d to forward\n", i);
      }
      break;
    case COMMAND_REVERSE:
      i = read_hex(st);
      if (i == ALL) {
        for (c = 0; c < NUM_MOTORS; c++) {
          set_motor_dir(c, MOTOR_DIR_REVERSE);
          printf("setting motor %d to reverse\n", c);
        }
      } else if (i < 0 || i >= NUM_MOTORS) {
        printf("motor # invalid\n");
      } else {
        set_motor_dir(i, MOTOR_DIR_REVERSE);
        printf("setting motor %d to reverse\n", i);
      }
      break;
    case COMMAND_DUTY_CYCLE:
      i = read_hex(st);
      if (i == ALL) {
        dc = read_hex(st + 2);
        if (dc < 0) {
          printf("duty cycle # invalid\n");
        } else {
          for (c = 0; c < NUM_MOTORS; c++) {
            set_motor_duty_cycle(c, dc);
            printf("setting motor %d to duty cycle %d\n", c, dc);
          }
        }
      } else if (i < 0 || i >= NUM_MOTORS) {
        printf("motor # invalid\n");
      } else {
        dc = read_hex(st + 2);
        if (dc < 0) {
          printf("duty cycle # invalid\n");
        } else {
          set_motor_duty_cycle(i, dc);
          printf("setting motor %d to duty cycle %d\n", i, dc);
        }
      }
      break;
    case COMMAND_FREQ:
      i = read_hex(st);
      set_pwm_freq(i);
      printf("PWM frequency set to: %d\n", i);
      for (i = 0; i < NUM_MOTORS; i++) {
        set_motor_duty_cycle(i, get_motor_duty_cycle(i));
      }
      break;
    case COMMAND_ACCEL:
      get_imu_orientation(&orientation);
      print_int(orientation.yaw);
      alt_putchar(',');
      print_int(orientation.pitch);
      alt_putchar(',');
      print_int(orientation.roll);
      alt_putchar('\n');
      break;
    case COMMAND_ACCEL_X:
      get_accel(&accel_data);
      print_int(accel_data.x);
      alt_putchar('\n');
      break;
    case COMMAND_ACCEL_Y:
      get_accel(&accel_data);
      print_int(accel_data.y);
      alt_putchar('\n');
      break;
    case COMMAND_ACCEL_Z:
      get_accel(&accel_data);
      print_int(accel_data.z);
      alt_putchar('\n');
      break;
    case COMMAND_DEPTH:
      i = get_user_depth();
      print_int(i);
      alt_putchar('\n');
      break;
    case COMMAND_MOTORS:
      print_int(get_pwm_freq());
      alt_putchar('\n');
      alt_putchar(get_motor_dir(0));
      for (i = 1; i < NUM_MOTORS; i++) {
        alt_putchar(',');
        alt_putchar(get_motor_dir(i));
      }
      alt_putchar('\n');
      print_int(get_motor_duty_cycle(0));
      for (i = 1; i < NUM_MOTORS; i++) {
        alt_putchar(',');
        print_int(get_motor_duty_cycle(i));
      }
      alt_putchar('\n');
      break;
    case COMMAND_SPEED:
      i = read_hex(st);
      set_target_speed(i);
      break;
    case COMMAND_HEADING:
      i = read_hex(st);
      set_target_heading(i);
      break;
    case COMMAND_SET_DEPTH:
      i = read_hex(st);
      set_target_depth(i);
      printf("setting target depth to %d\n", i);
      break;
    case COMMAND_CONTROLLER:
      i = read_hex(st);
      set_controller(i);
      printf("setting controller %s\n", (i % 2  == 0) ? "off" : "on");
      break;
    case COMMAND_IMU_SHELL:
      printf("type quit to exit IMU shell\n");
      rs232_shell();
      break;
    case COMMAND_PID_DEPTH:
      sscanf(st, " %lf %lf %lf %lf", &P, &I, &D, &Alpha);
      set_pid_constants_depth(P, I, D, Alpha);
      break;
    case COMMAND_PID_PITCH:
      sscanf(st, " %lf %lf %lf %lf", &P, &I, &D, &Alpha);
      set_pid_constants_pitch(P, I, D, Alpha);
      break;
    case COMMAND_PID_ROLL:
      sscanf(st, " %lf %lf %lf %lf", &P, &I, &D, &Alpha);
      set_pid_constants_roll(P, I, D, Alpha);
      break;
    case COMMAND_PID_YAW:
      sscanf(st, " %lf %lf %lf %lf", &P, &I, &D, &Alpha);
      set_pid_constants_yaw(P, I, D, Alpha);
      break;
  }
}

// the main function
int main()
{
  char buffer_str[STR_LEN+1];

  init();

  // read and process commands continuously
  while(1) {
    alt_getline(buffer_str, STR_LEN);
    process_command(buffer_str);
  }

  return 0;
}
