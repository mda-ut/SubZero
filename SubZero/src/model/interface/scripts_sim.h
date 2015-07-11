/*
This header file allows C and C++ files to access the FPGA software (such as script C files or the main code in interface/).
init_fpga() must be called before any FPGA API is called (ie to get depth or set target yaw) because this creates a process
to communicate with the FPGA. This also creates signal handlers that try to exit gracefully on signals (most notably Ctrl+C).

Note: the function definitions are declared as 'inline' to link properly because this is a header file.

Victor Zhang - Sept 2013
*/


#ifndef SCRIPTS_SIM_H
#define SCRIPTS_SIM_H

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fpga_sim_ui.h"

#ifdef __cplusplus
extern "C" {
#endif

void init_fpga_sim();

#ifdef __cplusplus
}
#endif

inline void int_handler_sim(int signal)
{
  // ignore SIGCHLD
  if (signal == SIGCHLD) {
    return;
  }

  // Second Ctrl+C will be raised to a kill
  static bool killed = false;
  if (killed) {
    raise(SIGKILL);
  }

  killed = true;

  // If the power is already off, just kill child and exit
  if (!get_power_sim()) {
    kill_child_sim();
    exit(0);
  }

  // Calling the int_handler will kill the child process (nios2-terminal)
  // Respawn it, then exit_safe
  spawn_term_sim(NULL);

  exit_safe_sim();
}

inline void init_fpga_sim()
{
  static bool initialized = false;
  if (initialized) {
    return;
  }

  // Fork a nios2-terminal for communication
  spawn_term_sim(NULL);

//  // Call int_handler on SIGINT (Ctrl+C)
//  signal(SIGINT, int_handler_sim);
//  // Call int_handler on SIGCHLD as well
//  signal(SIGCHLD, int_handler_sim);

  initialized = true;
}

#endif // SCRIPTS_SIM_H
