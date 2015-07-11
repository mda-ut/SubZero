#include "fpga_sim_ui.h"

#include <curses.h>

#include <assert.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define ZERO_DC 512
#define PWM_FREQ 20
#define FLUSH_MASK 0x3

unsigned cmd_ok_sim = 0;

static unsigned power = 0;
static int verbose = 1;
static int flush_counter = 0;

//static pid_t child_pid = 0;
//static int p_stdin[2], p_stdout[2];
static FILE *infp = NULL, *outfp = NULL, *logfp = NULL;

int atoi_safe_sim (char *str) {
    if (str == NULL) {
        printf ("Invalid input to atoi.\n");
        return 0;
    }
    return atoi (str);
}

/* ============================================================================
 * FUNCTIONS TO PIGGYBACK SIMFISHY
 * ============================================================================
 * These functions are required for subzero to piggyback SIMfishy. Copy the
 * parallel codes to update this class but DON'T DELETE OR CHANGE THESE FUNCS :D
 *
 * NOTE: when copying, check for all fprintf instances and replace them with
 * write_and_flush_term_sim(); otherwise, there may be untold consequences...
 */

int cmpstr(char* str1,char* str2)
{
    if (strcmp(str1,str2) == 0)
        return 1;
    return 0;
}

void openStream (int stream)
{
    if(stream == 0)
    {
        infp = fopen("infp.txt","w");
        if (infp == 0)
            printf("infp not open!");
    }
    if(stream == 1)
    {
        outfp = fopen("outfp.txt","r");
        if (outfp == 0)
            printf("outfp not open!");
    }
    if(stream == 2)
    {
        logfp = fopen("inlogfp.txt","w");
        if (logfp == 0)
            printf("logfp not open!");
    }
}

void closeStream (int stream)
{
    if (stream == 0)
        fclose(infp);
    if (stream == 1)
        fclose(outfp);
    if (stream == 2)
        fclose(logfp);
}

void spawn_term_sim (char *proc)
{
    openStream(0);
    openStream(1);
    openStream(2);
}

void clearInfp()
{
    closeStream(0);
    openStream(0);
}

void write_and_flush_term_sim (char* cmd)
{
    unsigned int BUF_SIZE = 128;
    char buf[BUF_SIZE];
    long size = 0;
    char power_fail_msg[] = "power failed\n";

    // clear and write to infp and also log it
    clearInfp();
    fprintf(infp,"%s",cmd);
    fprintf(logfp,"%s",cmd);
    fflush(logfp);
    fflush(infp);

    while (1) {

        // update the outfp file..
        fflush(outfp);

        // updates the size of the outfp file.. when size is > 0, there is new output to read
        rewind(outfp);
        fseek(outfp,0,SEEK_END);
        size = ftell(outfp);
        rewind(outfp);

        if (size > 0)
        {
            fgets(buf,BUF_SIZE,outfp);

            // in event that SIMfishy is terminated before SubZero
            if (strcmp(&buf[0],power_fail_msg)==0) {
                clearInfp();
                power = 0;
                printf("%s\n", buf);
                exit(0);  // parallel to fpga_ui.c code.. this will terminate SubZero.
                break;
            }

            // in noremal even where a output to the outfp is recognized to be the cmd input to infp
            if (strcmp(&buf[0],cmd)==0) {
                clearInfp(); // this clear step tells SIMfishy that there is no cmd anymore&& is vital since after each cmd read, SIMfishy will wait for infp to be cleared before reading the next cmd
                break;
            }
        }
    }
}

void kill_child_sim ()
{
    closeStream(0);
    closeStream(1);
    closeStream(2);
//    close(p_stdin[0]);
//    close(p_stdout[1]);
//    if (child_pid > 0) {
//       kill(child_pid, SIGTERM);
//    }
}

pid_t popen2_sim (char *proc, int *infp, int *outfp)
{
}

/* ===============================================================================
 * END PIGGYBACK CODES
 * ===============================================================================
 */



void cmd_error_sim () { printf ("**** Invalid command. Type \"help\" for command list\n"); }


void exit_safe_sim ()
{
//    power_off_sim();
    kill_child_sim();

    exit(0);
}


void help_sim () {
    cmd_ok_sim = 1;
    printf ("\n\tCommands go by the format <system> <options>, like \"power on\"\n");
    printf ("\n\tDo \"help <system>\" to print the options of that system.\n");
    printf ("\t\"q\" to quit.\n");
    printf ("\n\tList of commands\n\t\tmotor / m\n\t\tdyn / d\n\t\tpower / p\n\n");
}

void help_motor_sim () {
    cmd_ok_sim = 1;
    printf ("\n\tmotor / m\n");
    printf ("\t\t%-10s - %s","status","print each motor's PWM value. PWM values range from -100 to 100\n");
    printf ("\t\t%-10s - %s","<N> <pwm>","set motor N to PWM value pwm. For example \"motor 3 -55\".\n");
    printf ("\t\t%-10s - %s","all stop","stop all motors.\n");
    printf ("\t\t%-10s - %s","fwd <pwm>","set the 2 horizontal motors to pwm.\n");
    printf ("\t\t%-10s - %s","rise <pwm>","set the 3 vertical motors to pwm.\n\n");
}

void help_dyn_sim () {
    cmd_ok_sim = 1;
    printf ("\n\tdyn / d\n");
    printf ("\t\t%-10s - %s","status","prints accelerometer and depth readings.\n");
    printf ("\t\t%-10s - %s","depth <pwm>","set target depth.\n\n");
}

void help_power_sim () {
    cmd_ok_sim = 1;
    printf ("\n\tpower / p\n");
    printf ("\t\t%-10s - %s","status","prints power status.\n");
    printf ("\t\t%-10s - %s","on / 1","turns power on.\n");
    printf ("\t\t%-10s - %s","start / 2","turns power on and turns on controllers.\n");
    printf ("\t\t%-10s - %s","off / 0","turns power off.\n\n");
}

void motor_status_sim() {
    cmd_ok_sim = 1;
    write_and_flush_term_sim ("gm\n");

    int pwm, i;
    char line[64];
    const int num_motors = 5;
    int duty_cycles[num_motors];

    assert(fscanf(outfp, "%d", &pwm) != EOF);
    printf("pwm: %d\n", pwm);

    assert(fscanf(outfp, "%s", line) != EOF);
    printf("motor directions: %s\n", line);

    assert(fscanf(outfp, "%d,%d,%d,%d,%d", duty_cycles, duty_cycles+1, duty_cycles+2, duty_cycles+3, duty_cycles+4) != EOF);
    printf("duty cycles:");
    for (i = 0; i < num_motors; i++) {
       printf(" %d", (duty_cycles[i]-512) * 100 / 512);
    }
    puts("");
}

void motor_set_sim (int pwm, char motor_flags) {
    cmd_ok_sim = 1;
    if (pwm < -PWM_MAX || pwm > PWM_MAX) {
        printf ("**** Invalid pwm. motor pwm unchanged.\n");
        return;
    }

    // convert pwm to something the FPGA understands
    int motor_pwm = (pwm + 100) * 1024 / 200;

    if (motor_flags & H_FRONT_LEFT) {
        printf ("set left front vertical motor to %d\n", pwm);
        fprintf (infp, "smd %d %x\n", M_FRONT_LEFT, motor_pwm);
    }
    if (motor_flags & H_FRONT_RIGHT) {
        printf ("set right front vertical motor to %d\n", pwm);
        fprintf (infp, "smd %d %x\n", M_FRONT_RIGHT, motor_pwm);
    }
    if (motor_flags & H_FWD_LEFT) {
        printf ("set left forward motor to %d\n", pwm);
        fprintf (infp, "smd %d %x\n", M_FWD_LEFT, motor_pwm);
    }
    if (motor_flags & H_FWD_RIGHT) {
        printf ("set right forward motor to %d\n", pwm);
        fprintf (infp, "smd %d %x\n", M_FWD_RIGHT, motor_pwm);
    }
    if (motor_flags & H_REAR) {
        printf ("set rear vertical motor to %d\n", pwm);
        fprintf (infp, "smd %d %x\n", M_REAR, motor_pwm);
    }

    fflush(infp);
}

void power_status_sim () {
    cmd_ok_sim = 1;
    printf("power is turned %s\n", (power) ? "on" : "off");
}

void power_on_sim () {
    cmd_ok_sim = 1;

    // Disable motors first
    fprintf (infp, "sms a\n");
    fprintf (infp, "sc 0\n");

    // Make sure the power is on
    write_and_flush_term_sim ("p 1\n");
    fprintf (infp, "spf %x\n", PWM_FREQ);

    power = 1;
    if (verbose) printf ("turned power on.\n");
}

void startup_sequence_sim () {
    cmd_ok_sim = 1;

    // Disable motors first
    fprintf (infp, "sms a\n");
    fprintf (infp, "sc 0\n");

    // Make sure the power is on
    write_and_flush_term_sim ("p 1\n");
    fprintf (infp, "spf %x\n", PWM_FREQ);

    // Wait before turning motors on at neutral duty cycle
    sleep(1);
    fprintf (infp, "smf a\n");

    // Wait before turning controller on
    sleep(1);
    fprintf (infp, "sc 1\n");

    fflush(infp);

    power = 1;
    if (verbose) printf ("started startup sequence.\n");
}

void power_off_sim () {
    if (!infp) {
        return;
    }

    cmd_ok_sim = 1;

    write_and_flush_term_sim("sms a\n");
    write_and_flush_term_sim("sc 0\n");

    // Make sure the power is off
    write_and_flush_term_sim ("p 0\n");

    power = 0;
    if (verbose) printf ("turned power off.\n");
}

int get_power_sim() {
    return power;
}

void get_accel_sim (int *x, int *y, int *z) {
    write_and_flush_term_sim("gax\n");
    assert(fscanf(outfp, "%d", x) != EOF);
    write_and_flush_term_sim("gay\n");
    assert(fscanf(outfp, "%d", y) != EOF);
    write_and_flush_term_sim("gaz\n");
    assert(fscanf(outfp, "%d", z) != EOF);
}

int get_yaw_sim () {
    int yaw;
    write_and_flush_term_sim("ga\n");
    assert(fscanf(outfp, "%d", &yaw) != EOF);
    // Also write the output to a log file
    FILE *log = fopen("log.txt", "a");
    fprintf(log, "%d", yaw);
    fclose(log);
    return yaw;
}

int get_depth_sim () {
    int depth;
    write_and_flush_term_sim("gd\n");
    assert(fscanf(outfp, "%d", &depth) != EOF);
    // Also write the output to a log file
    FILE *log = fopen("log.txt", "a");
    fprintf(log, "%d", depth);
    fclose(log);
    return depth;
}

void dyn_status_sim () {
    cmd_ok_sim = 1;
    int x, y, z;

    get_accel_sim(&x, &y, &z);
    printf("(x,y,z) acceleration: %d,%d,%d\n", x, y, z);

    int z_squared = z*z, y_squared = y*y;
    const double RAD_TO_DEG = 57.3; // 180/PI

    // pitch and roll are zero when sub is "flat"
    double pitch = (z_squared + y_squared == 0) ? 90 : atan2(x,sqrt(z_squared + y_squared)) * RAD_TO_DEG;
    double roll = (z_squared == 0) ? 90 : atan2(y,sqrt(2*z_squared)) * RAD_TO_DEG;

    printf("pitch: %d, roll: %d (both in degrees)\n", (int)pitch, (int)roll);

    int d = get_depth_sim();
    printf("depth: %d\n", d);
}

// Flush the output every so often so polling remains responsive
void flush_output_sim()
{
    flush_counter++;
    if ((flush_counter & FLUSH_MASK) == 0) {
        write_and_flush_term_sim("gd\n");
    }
}

void dyn_set_target_speed_sim (int target_speed) {
    cmd_ok_sim = 1;
    if (verbose) printf("setting target speed to %d.\n", target_speed);
    fprintf(infp, "ss %x\n", target_speed);
    fflush(infp);

    flush_output_sim();
}

void dyn_set_target_depth_sim (int target_depth) {
    cmd_ok_sim = 1;
    if (verbose) printf("setting target depth to %d.\n", target_depth);
    fprintf(infp, "sd %x\n", target_depth);
    fflush(infp);

    flush_output_sim();
}

void dyn_set_target_yaw_sim (int target_yaw) {
    cmd_ok_sim = 1;
    if (verbose) printf("setting target yaw to %d.\n", target_yaw);
    fprintf(infp, "sh %x\n", target_yaw);
    fflush(infp);

    flush_output_sim();
}

void set_pid_depth_sim(double P, double I, double D, double Alpha) {
    cmd_ok_sim = 1;
    fprintf(infp, "spcd %lf %lf %lf %lf\n", P, I, D, Alpha);
    fflush(infp);
}

void set_pid_pitch_sim(double P, double I, double D, double Alpha) {
    cmd_ok_sim = 1;
    fprintf(infp, "spcp %lf %lf %lf %lf\n", P, I, D, Alpha);
    fflush(infp);
}

void set_pid_roll_sim(double P, double I, double D, double Alpha) {
    cmd_ok_sim = 1;
    fprintf(infp, "spcr %lf %lf %lf %lf\n", P, I, D, Alpha);
    fflush(infp);
}

void set_pid_yaw_sim(double P, double I, double D, double Alpha) {
    cmd_ok_sim = 1;
    fprintf(infp, "spcy %lf %lf %lf %lf\n", P, I, D, Alpha);
    fflush(infp);
}

void set_verbose_sim(int v) {
    verbose = v;
}
