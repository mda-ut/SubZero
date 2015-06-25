/**
 * FPGAInterface.h
 *
 * Created on: Jan 17, 2015
 * Author: ahsueh1996
 */

#ifndef FPGAINTERFACE_H_
#define FPGAINTERFACE_H_

#include <thread>
#include <iostream>
#include "HwInterface.h"
#include "../../util/data/Data.h"
#include "../../util/data/FPGAData.h"

using namespace std;

enum Attributes {
	POWER,
	DEPTH,
	HEADING, // absolute, given by sonar
	YAW, // relative to the direction the sub is heading
	SPEED
};

//enum MoveCommands : Commands {
//	FORWARD,
//	REVERSE,
//	LEFT,
//	RIGHT,
//	SINK,
//	RISE
//};

//enum SpecialCommands : Commands {
//	POWERON,
//	POWEROFF,
//  // from previous year, AquaTux also had:
//  // SUB_STARTUP_SEQUENCE,
//  // SUB_MISSION_STARTUP_SEQUENCE,
//  // SUB_POWER_OFF,
//  // SIM_MOVE_FWD,
//  // SIM_MOVE_REV,
//  // SIM_MOVE_LEFT,
//  // SIM_MOVE_RIGHT,
//  // SIM_MOVE_RISE,
//  // SIM_MOVE_SINK,
//  // SIM_ACCEL_ZERO
//};

/**
 * A concrete child of HwInterface that deals specifically with the FPGA.
 *
 * FPGAInterface is responsible for:
 * 		1. Dealing with the data coming from FPGA: poll->decode
 * 		2. Managing its private buffer: store the new, delete the old
 * 		3. Dealing with the data going to the hardware: encode->send
 * 			- i.e. provide function that delivers commands and instructions
 * 			  to the FPGA (
 * 			  NOTE: only providing the functions to command not actually
 * 			  commanding. Submarine level thinking is done in the Controller.
 *
 * @version	0.0
 * @since	Jan 17 2015
 */

class FPGAInterface : public HwInterface {

private:

	std::thread readThread; // need c++11

	/* ==========================================================================
	 * 				INTERACTING WITH DATA COMING IN (FROM FPGA)
	 * ==========================================================================
	 * This interface class will be automatically polling and managing
	 * the polling process privately within the interface at pollFrequency
	 * using the functions below.
	 */

	/**
	 * Poll raw data from FPGA.
	 */
	virtual void poll();

	/**
	 * Decode the data.
	 * @param	data	data to be decoded
	 * @return	decoded data in a FPGAData format
   	 */
	virtual FPGAData* decode(string* data);

protected:

	/* ==========================================================================
	 * 							MANAGING DATA BUFFER
	 * ==========================================================================
	 * The data buffer will be managed automatically and privately by this class.
	 * These functions are defined and implemented in the root parent class i.e.
	 * in HwInterface.
	 */

	/**
	 * Delete buffer from startIdx to endIdx
	 */
	virtual void deleteFromBuffer();

	/**
	  * Store decoded data to buffer.
	  * @param	data	data to be stored to buffer.
	  */
	virtual void storeToBuffer(Data* data);

	/**
	 * Procedures to execute for the FPGA reading thread.
	 */
	void in();

public:

	/* ==========================================================================
	 * 				INTERACTING WITH DATA GOING OUT (TO FPGA)
	 * ==========================================================================
	 * FPGAInterface provides functions for the Controller to send data/commands/
	 * messages to the FPGA.
	 */

	/**
	 * Encodes the data to be sent to FPGA.
	 * @param	data	data to be encoded
	 * @return	encoded data in FPGA-understandable format
	 */
//	virtual string* encode(FPGAData data); //might not be needed

	/**
	 * Encodes the command to be sent to FPGA.
	 * @param	data	data to be encoded
	 * @return	encoded data in FPGA-understandable format
	 */
	//@Overload
//	virtual string* encode(Commands command);

	/**
	 * Give commands to FPGA.
	 * @param	attr	attribute to set
	 * @param	value	set attribute to this value
	 */
	void set(Attributes attr, int value);

	/**
	 * Send the data.
	 * @param	data	data to be sent
   	 */
	virtual void send(string* data);

	/* ==========================================================================
	 * 								GETTERS AND SETTERS
	 * ==========================================================================
	 */

	/**
	 * Return the most recent buffer data.
	 * This function is defined and implemented by the parent class (HwInterface).
	 * @return	Data*	the most recent data in buffer
	 *
	 */
	virtual Data* getDataFromBuffer();

	/**
	 * Get the frequency of data polling (polls per second).
	 * @return	polling frequency i.e. sampling rate
	 */
	virtual int getPollFrequency();

	/**
	 * Set the frequency of data polling.
	 * @param	frequency	number of polls per second
	 */
	virtual void setPollFrequency(int frequency);

	/**
	 * Get size of buffer.
	 * @return	size of the buffer
	 */
	virtual int getBufferSize();

	/**
	 * Set size of buffer.
	 * @param	bufferSize	reset buffer size to this
	 */
	virtual void setBufferSize(int bufferSize);


	/* ==========================================================================
	 * 							CONSTRUCTOR AND DESTRUCTOR
	 * ==========================================================================
	 */

	/**
	 * Constructor for FPGA Interface
	 * @param	bufferSize	buffer size for the interface
	 * @param	pollFrequency	frequency of polling (polls per second)
	 */
	FPGAInterface(int bufferSize, int pollFrequency);


	/**
	 * Destructor
	 */
	virtual ~FPGAInterface();

};


#endif 


/* FPGAINTERFACE_H_ */
