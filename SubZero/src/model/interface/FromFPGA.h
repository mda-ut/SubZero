/*
 * FromFPGA.h
 *
 * Created on: Feb 28, 2015
 * Author: ehsueh
 */

#ifndef FROMFPGA_H_
#define FROMFPGA_H_

/** 
 * FromFPGA is the part of the interface that deals with the inputs from the fpga
 * and prepare them for use by the software.
 */

class FromFPGA {
  
  public: 
  virtual ~FromFPGA() {}

  // some set functions ....

};

class FromFPGA {
  
  public: 
  virtual ~FromFPGA() {}

  // add some set functions ....

};


/* 
 * the real implementation to be used by the submarine 
 */
class FromFPGASub : FromFPGA {
  
};

/* 
 * a don't-care, dummy implementation 
 */
class FromFPGADummy : FromFPGA {
  
};

/* 
 * implementation for the simulation
 */
class FromFPGASim : FromFPGA {
  
};


#endif


/* FROMFPGA_H_*/