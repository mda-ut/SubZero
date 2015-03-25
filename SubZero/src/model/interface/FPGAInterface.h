/*
 * FPGAInterface.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef FPGAINTERFACE_H_
#define FPGAINTERFACE_H_

#include "HwInterface.h"
#include "DataDefinition.h"
 // include some other fpga specific classes

enum MoveCommands {
  FORWARD,
  REVERSE,
  LEFT,
  RIGHT,
  SINK,
  RISE
};

enum SpecialCommands{
  POWERON,
  POWEROFF,
  // from previous year, AquaTux also had:
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

/**
 * A child of HwInterface that deals specifically with the FPGA. Concrete class.
 */
class FPGAInterface : public HwInterface {

  private:

    /* 
     * private helper function for send
     * enocde data to be sent to hardware
     * encode the msg at pointer String src (source)
     * output results to location at pointer FpgaData des(tination) 
     */
    virtual int encode(String* src, FpgaData* des); 
    
    /*
     * this class will be automatically pulling and managing
     * the pulling process privately within the interface
     * using the following functions
     */
    virtual int pullTo(String* des); // pull raw data from hardware at pullFrequency to des(tination) as specified
    virtual int decode(String* src, FpgaData* des); // decode the String at src and store at FpgaData des(tination)

protected:

    virtual int deleteFromBuffer(int startIdx, int endIdx); // delete from startIdx to endIdx inclusively
    virtual int storeToBuffer(FpgaData* src); // store decoded data at src to buffer

public:

    virtual int copyFromBuffer(int startIdx, int endIdx, FpgaData** src); // copy from [startIdx, endIdx]
    virtual int send(FpgaData* src); // send data at src to hardware indicated by hardwareID   

    /*
     * getters and setters for the private fields
     */
    virtual int getPullFrequency();
    virtual int setPullFrequency(int frequency);
    virtual int getBufferSize();
    virtual int setBufferSize(int bufferSize);
    
    /*
     * constructors and destructors
     */
    FPGAInterface(int bufferSize, int pullFrequency, int policy, int hardwareID);
    virtual ~FPGAInterface();

};


#endif 


/* FPGAINTERFACE_H_ */