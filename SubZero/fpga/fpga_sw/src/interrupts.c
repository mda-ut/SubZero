/*
 * interrupts.c
 *
 * The timer and power management interrupts.
 *
 * The power management interrupt is triggered whenever a specific voltage
 * does not meet its threshold (either by under-voltage or over-voltage). This interrupt
 * allows the software to gather stats and decide when to actually turn off power.
 * Important: the hardware does not power off itself, but relies on software to do so.
 *
 * Timer interrupt is triggered at a constant interval, and is currently used to call the  controller code,
 * through calculate_pid() and update_depth_reading(). Separate timers can be used it different intervals are needed,
 * though one should suffice with modular arithmetic (ie see how update_depth_reading() is called more often).
 *
 * Update: calculate_pid() is not called directly here since it is potentially slow code. Interrupt handlers should be fast.
 * Instead, an update_pid flag is set to 1 and a scheduler in utils.c will schedule the calculate_pid() call.
 *
 * Author: victor
 */

#include "altera_avalon_timer_regs.h"
#include "system.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"

#include "controller.h"
#include "interrupts.h"
#include "rs232.h"
#include "settings.h"
#include "utils.h"

// For power management
int power_failures[7] = {0};
int old_power_failures[7] = {0};

int enable_controller = 0;

// Flag to update pid in main loop
int update_pid = 0;

// Return time-averaged depth if possible to give a sense of
// what depth the controller is using
int get_user_depth()
{
  if (enable_controller) {
    return get_average_depth();
  }
  return get_depth();
}

void set_controller(int status)
{
   enable_controller = status;
   if (enable_controller) {
     struct orientation o;
     get_imu_orientation(&o);
     set_target_speed(0);
     set_target_heading(o.yaw);
     set_target_depth(get_depth());

     IOWR_ALTERA_AVALON_TIMER_CONTROL(CONTROLLER_INTERRUPT_COUNTER_BASE, 7); // Start timer interrupt
   } else {
      // Turn off all motors
      int i;
      for (i = 0; i < NUM_MOTORS; i++) {
         set_motor_duty_cycle(i, ZERO_PWM);
      }
   }
}

// Controller Interrupt Routine, should be 100Hz.
static void timer_interrupts(void* context, alt_u32 id)
{
   // Power stuff
   int i;
   for (i = 0; i < 7; i++) {
      // Reset to 0 if unchanged
      if (power_failures[i] == old_power_failures[i]) {
         power_failures[i] = 0;
      }
      old_power_failures[i] = power_failures[i];
   }

   update_depth_reading();

   static unsigned counter = 0;
   counter++;

   if (counter % NUM_DEPTH_VALUES == 0) {
      update_pid = 1;
   }
   
   // Restart Interrupt for this timer
   IOWR_ALTERA_AVALON_TIMER_SNAPL(CONTROLLER_INTERRUPT_COUNTER_BASE, 1);
   IOWR_ALTERA_AVALON_TIMER_CONTROL(CONTROLLER_INTERRUPT_COUNTER_BASE,0); // Clear interrupt (ITO)
   IOWR_ALTERA_AVALON_TIMER_STATUS(CONTROLLER_INTERRUPT_COUNTER_BASE, 0); // Clear TO
   if (enable_controller) {
      IOWR_ALTERA_AVALON_TIMER_CONTROL(CONTROLLER_INTERRUPT_COUNTER_BASE,7); // Enable IRQ and Start timer
   }
}

// Power management Interrupt routine
//
// If this triggers, something went wrong with one of the voltage lines
// Turn off power to all the voltage rails and print out what caused
// the problem
static void pm_interrupt(void *context, alt_u32 id)
{
   // Get failing voltage line
   int which_failed = IORD(POWER_MANAGEMENT_SLAVE_0_BASE, 0);

   if (which_failed == 5 || which_failed == 6) return; // ignore 3.3V failures.
   power_failures[which_failed]++;

   static const int failure_threshold = 100;
   if (power_failures[which_failed] < failure_threshold) {
      return;
   }

   // Turn off power
   IOWR(POWER_MANAGEMENT_SLAVE_0_BASE, 0, 0);

   // Might be in the middle of printing, print a leading newline
   alt_printf("\npower failed\n");
   int i;
   for (i = 0; i < 7; i++) {
      if (power_failures[i] == 0) {
         continue;
      }
      switch(i) {
         case 0:
            alt_putstr("24 V under-voltage failed ");
            break;
         case 1:
            alt_putstr("12 V over-voltage failed ");
            break;
         case 2:
            alt_putstr("12 V under-voltage failed ");
            break;
         case 3:
            alt_putstr("5 over-voltage failed ");
            break;
         case 4:
            alt_putstr("5 V under-voltage failed ");
            break;
         case 5:
            alt_putstr("3.3 V over-voltage failed ");
            break;
         case 6:
            alt_putstr("3.3 V under-voltage failed ");
            break;
       }
       print_int(power_failures[i]);
       alt_putstr(" times\n");
   }
}

void init_interrupts()
{
   // Setup power management interrupt
   alt_ic_isr_register(POWER_MANAGEMENT_SLAVE_0_IRQ_INTERRUPT_CONTROLLER_ID, POWER_MANAGEMENT_SLAVE_0_IRQ,(void *)pm_interrupt,0,0); // Register Interrupt (check system.h for defs)

   const int timer_period = CLOCK_SPEED / TIMER_RATE_IN_HZ / NUM_DEPTH_VALUES;
   const short period_lo = timer_period;
   const short period_hi = timer_period >> 16;

   // Setup controller interrupt
   alt_ic_isr_register(CONTROLLER_INTERRUPT_COUNTER_IRQ_INTERRUPT_CONTROLLER_ID,CONTROLLER_INTERRUPT_COUNTER_IRQ,(void *)timer_interrupts,0,0); // Register Interrupt (check system.h for defs)
   IOWR_ALTERA_AVALON_TIMER_CONTROL(CONTROLLER_INTERRUPT_COUNTER_BASE, 0); // Clear control register
   IOWR_ALTERA_AVALON_TIMER_CONTROL(CONTROLLER_INTERRUPT_COUNTER_BASE, 2); // Continuous Mode ON
   IOWR_ALTERA_AVALON_TIMER_PERIODL(CONTROLLER_INTERRUPT_COUNTER_BASE, period_lo); // Timer interrupt period
   IOWR_ALTERA_AVALON_TIMER_PERIODH(CONTROLLER_INTERRUPT_COUNTER_BASE, period_hi);
   IOWR_ALTERA_AVALON_TIMER_CONTROL(CONTROLLER_INTERRUPT_COUNTER_BASE, 3); // Enable timer_0 interrupt
   if (enable_controller) {
      IOWR_ALTERA_AVALON_TIMER_CONTROL(CONTROLLER_INTERRUPT_COUNTER_BASE, 7); // Start timer interrupt
   }
}
