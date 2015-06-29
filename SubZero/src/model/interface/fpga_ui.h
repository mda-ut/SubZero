#ifndef FPGA_UI_H
#define FPGA_UI_H

#define PWM_MAX 100

#define H_FRONT_LEFT 0x1 // in hex
#define H_FRONT_RIGHT 0x2
#define H_FWD_LEFT 0x4
#define H_FWD_RIGHT 0x8
#define H_REAR 0x10
#define M_FRONT_LEFT 0 // in decimal
#define M_FRONT_RIGHT 1
#define M_FWD_LEFT 2
#define M_FWD_RIGHT 3
#define M_REAR 4

#define H_FWD 0xc
#define H_RISE 0x13
#define H_ALL 0x1f

extern unsigned cmd_ok;

int atoi_safe (char *str);

#ifdef __cplusplus
extern "C" {
#endif

void kill_child ();
void exit_safe ();
void cmd_error ();

void spawn_term (char *);

void help ();
void help_motor ();
void help_dyn ();
void help_power ();

void motor_status();
void motor_set (int pwm, char motor_flags);

void power_status();
void power_on();
void startup_sequence();
void power_off();
int get_power();

void dyn_status();
void dyn_set_target_speed(int);
void dyn_set_target_depth(int);
void dyn_set_target_yaw(int);

void get_accel(int *, int *, int *);
int get_yaw();
int get_depth();

void set_pid_depth(double, double, double, double);
void set_pid_pitch(double, double, double, double);
void set_pid_roll(double, double, double, double);
void set_pid_yaw(double, double, double, double);

void set_verbose(int);

#ifdef __cplusplus
}
#endif

#endif
