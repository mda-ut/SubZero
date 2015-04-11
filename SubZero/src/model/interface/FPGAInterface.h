/**
 * FPGAInterface.h
 *
 * Created on: Jan 17, 2015
 * Author: ahsueh1996
 */

#ifndef FPGAINTERFACE_H_
#define FPGAINTERFACE_H_

#include "HwInterface.h"
#include "Data.h"

using namespace std;

enum Commands {
};

enum MoveCommands : Commands {
	FORWARD,
	REVERSE,
	LEFT,
	RIGHT,
	SINK,
	RISE
};

enum SpecialCommands : Commands {
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

	/* ==========================================================================
	 * 				INTERACTING WITH DATA COMING IN (FROM FPGA)
	 * ==========================================================================
	 * This interface class will be automatically polling and managing
	 * the polling process privately within the interface at pollFrequency
	 * using the functions below.
	 */

	/**
	 * Poll raw data from FPGA.
	 * @return	data polled
	 */
	virtual string* poll();

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
	 * @param	stardIdx	start deleting from this index
	 * @param	endIdx	the index of the last data to delete
	 */
	virtual void deleteFromBuffer(int startIdx, int endIdx);

	/**
	  * Store decoded data to buffer.
	  * @param	data	data to be stored to buffer.
	  */
	virtual void storeToBuffer(Data* data);

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
	virtual string* encode(FPGAData data); //might not be needed

	/**
	 * Encodes the command to be sent to FPGA.
	 * @param	data	data to be encoded
	 * @return	encoded data in FPGA-understandable format
	 */
	@Overload
	virtual string* encode(Commands command);

	/**
	 * Send the data.
	 * @param	data	data to be sent
   	 */
	virtual void send(String* data);


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
	 * Return the data in buffer from startIdx to endIdx. Overloading the function
	 * above. (Also implemented in HwInterface.)
	 * @param	startIdx	get data starting at this index
	 * @param	endIdx	index of the last data to get
	 * @return	an array of data
	 */
	@Overload
	virtual Data* getDataFromBuffer(int startIdx, int endIdx);

	/**
	 * Get the frequency of data polling
	 * @return	polling frequency i.e. sampling rate
	 */
	virtual double getPollFrequency();

	/**
	 * Set the frequency of data polling/polling.
	 * @param	frequency	set polling to this frequency
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
	 * Constructor for Hardware Interface
	 * @param	bufferSize	buffer size for the interface
	 * @param	policy	specifies the encoding and decoding policy to be used
	 * @param	hardwareID	identifies the hardware this interface interacts with
	 */
	FPGAInterface(int bufferSize, int pullFrequency, int policy, int hardwareID);

	/**
	 * Destructor
	 */
	virtual ~FPGAInterface();

};


#endif 


/* FPGAINTERFACE_H_ */
