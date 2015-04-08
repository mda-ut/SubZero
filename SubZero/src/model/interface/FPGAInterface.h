/*
 * FPGAInterface.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef FPGAINTERFACE_H_
#define FPGAINTERFACE_H_


#include "HwInterface.h"
#include "Data.h"
#include <string>
using namespace std;
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

    /**
     * Private helper function for send().
     * Encode FPGAData into the string format instructions understandable by FPGA
	 * @param src
	 */
    virtual string* encode(FPGAData* src);
    
    /*
     * this class will be automatically pulling and managing
     * the pulling process privately within the interface
     * using the following functions
     */

	/**
	 * Pull raw data from hardware
	 */
    virtual string* pull();

    /**
     * Decode the data at src from string to FPGAData.
   	 */
    virtual FPGAData* decode(string* src);

  protected:

    /**
     * Delete buffer from startIdx to endIdx
     * @param startIdx, endIdx
     */
    virtual void deleteFromBuffer(int startIdx, int endIdx);


    /**
      * Store decoded data at src to buffer
      * @param src
      */
    virtual void storeToBuffer(Data* src);


  public:

    /**
     * Return the most recent buffer data
     *
     */
    virtual FPGAData* getDataFromBuffer();

    /**
     * Return the data in buffer from startIdx to endIdx
     * @param startIdx, endIdx
     */
    @Overload
    virtual FPGAData** getDataFromBuffer(int startIdx, int endIdx);

    /**
     * Send data at src to hardware indicated by hardwareID
     * @param src
     */
    virtual void send(Data* src);

    /**
     * Getters and setters for the private fields
     */

    /**
     * Get the frequency of data pulling/polling.
     */
    virtual double getPullFrequency();

    /**
     * Set the frequency of data pulling/polling.
     * @param frequency
     */
    virtual void setPullFrequency(int frequency);

    /**
     * Get size of buffer.
     */
    virtual int getBufferSize();

    /**
     * Set size of buffer.
     */
    virtual void setBufferSize(int bufferSize);

    /**
     * Constructor for FPGA Interface
     * @param bufferSize, pullFrequency, policy, hardwareID
     */
    FPGAInterface(int bufferSize, int pullFrequency, int policy, int hardwareID);

    /**
     * Destructor
     */
    virtual ~FPGAInterface();

};


#endif 


/* FPGAINTERFACE_H_ */
