#ifndef FPGA_SIM_UI_H
#define FPGA_SIM_UI_H

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

extern unsigned cmd_ok_sim;

int atoi_safe_sim (char *str);

#ifdef __cplusplus
extern "C" {
#endif

void kill_child_sim ();
void exit_safe_sim ();
void cmd_error_sim ();

void spawn_term_sim (char *);

void help_sim ();
void help_motor_sim ();
void help_dyn_sim ();
void help_power_sim ();

void motor_status_sim();
void motor_set_sim (int pwm, char motor_flags);

void power_status_sim();
void power_on_sim();
void startup_sequence_sim();
void power_off_sim();
int get_power_sim();

void dyn_status_sim();
void dyn_set_target_speed_sim(int);
void dyn_set_target_depth_sim(int);
void dyn_set_target_yaw_sim(int);

void get_accel_sim(int *, int *, int *);
int get_yaw_sim();
int get_depth_sim();

void set_pid_depth_sim(double, double, double, double);
void set_pid_pitch_sim(double, double, double, double);
void set_pid_roll_sim(double, double, double, double);
void set_pid_yaw_sim(double, double, double, double);

void set_verbose_sim(int);

#ifdef __cplusplus
}
#endif

#endif // FPGA_SIM_UI_H
