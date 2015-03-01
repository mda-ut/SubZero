/*
 * ToFPGA.h
 *
 * Created on: Mar 1, 2015
 * Author: ehsueh
 */

#ifndef TOFPGA_H_
#define TOFPGA_H_

/**
 * ToFPGA is the part of the interface that deals with outputs from software to hardware.
 * It is how software gives commands to fpga to move and instruct the submarine.
 */

enum MoveCommands {
  FORWARD,
  REVERSE,
  LEFT,
  RIGHT,
  SINK,
  RISE
};

enum Position {
  PITCH,
  ROLL,
  YAW,
  SPEED,
  DEPTH
};

enum SpecialCommands{
  POWERON,
  POWEROFF,
  // from previous year:
  // SUB_STARTUP_SEQUENCE,
  // SUB_MISSION_STARTUP_SEQUENCE,
  // SUB_POWER_OFF,
  // SIM_MOVE_FWD,
  // SIM_MOVE_REV,
  // SIM_MOVE_LEFT,
  // SIM_MOVE_RIGHT,
  // SIM_MOVE_RISE,
  // SIM_MOVE_SINK,
  // SIM_ACCEL_ZERO
};

class ToFPGA {
  
  public: 
  virtual ~ToFPGA() {}

  // add some set functions ....

};


/* 
 * the real implementation to be used by the submarine 
 */
class ToFPGASub : ToFPGA {
  
};

/* 
 * a don't-care, dummy implementation 
 */
class ToFPGADummy : ToFPGA {
  
};

/* 
 * implementation for the simulation
 */
class ToFPGASim : ToFPGA {
  
};


#endif


/* TOFPGA_H_ */