/*
This header file allows C and C++ files to access the FPGA software (such as script C files or the main code in interface/).
init_fpga() must be called before any FPGA API is called (ie to get depth or set target yaw) because this creates a process
to communicate with the FPGA. This also creates signal handlers that try to exit gracefully on signals (most notably Ctrl+C).

Note: the function definitions are declared as 'inline' to link properly because this is a header file.

Victor Zhang - Sept 2013
*/

#ifndef __MDA_SCRIPTS_H__
#define __MDA_SCRIPTS_H__

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Logger.h"
#include "fpga_ui.h"

#ifdef __cplusplus
extern "C" {
#endif

void init_signal_handler();
void init_fpga();

#ifdef __cplusplus
}
#endif

extern volatile int signal_quit;
static bool fpga_initialized = false;
inline void int_handler(int signal) {
  // ignore SIGCHLD
  if (signal == SIGCHLD) {
    return;
  }

  // Second Ctrl+C will be raised to a kill
  static bool killed = false;
  if (killed) {
    raise(SIGKILL);
  }
  printf("Ctrl+C detected.  Exiting...\n");
  killed = true;
  signal_quit = 1;

  if(fpga_initialized) {
      // If the power is already off, just kill child and exit
      if (!get_power()) {
          kill_child();
          exit(0);
      }

      // Calling the int_handler will kill the child process (nios2-terminal)
      // Respawn it, then exit_safe
      spawn_term(NULL);

      exit_safe();
  }
}

inline void init_signal_handler() {
    // Call int_handler on SIGINT (Ctrl+C)
    signal(SIGINT, int_handler);
    // Call int_handler on SIGCHLD as well
    signal(SIGCHLD, int_handler);
}

inline void init_fpga() {
  if (fpga_initialized) {
    return;
  }

  // Fork a nios2-terminal for communication
  spawn_term(NULL);

  fpga_initialized = true;
}

#endif
