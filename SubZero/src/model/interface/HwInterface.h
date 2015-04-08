/**
 * HwInterface.h
 *
 * Created on: Jan 17, 2015
 * Author: ahsueh1996
 */

#ifndef HWINTERFACE_H_
#define HWINTERFACE_H_

#include "Data.h"
// Data is the generic datatype defined in Data.h


/**
 * HwInterface is an abstract class responsible for all the io interfacing with hardware.
 */
class HwInterface {

private:

	/**
	 * Pointer to memory allocated for storing raw (but
	 * decoded) data from hardware.
	 */
	Data** decodedBuffer[];

	/**
	 * Allocate only enough memory to keep a max of
	 * this number of hardware inputs; discard all after that.
	 */
	int bufferSize;

	/**
	 * Pull data from hardware at this frequency.
	 */
	int pullFrequency;

	/**
	 * Specifies the encoding, decoding policy to use.
	 */
	int policy;
	/*
	 * alternatively, we can just implement encode(), decode() ... etc
	 * differently for each hardwares when we branch out
	 * from our abstract class
	 */

	/*
	 * ID of hardware this interface interacts with
	 * hardware can be accessed (somehow) via this ID
	 */
	int hardwareID;

	/**
	 * Private helper function for send().
	 * Encode the message at pointer Data src (source)
	 * @param src, des
	 */
	virtual void encode(Data* src);

	/**
	 * this class will be automatically pulling and managing
	 * the pulling process privately within the interface at pullFrequency
	 * using the following functions
	 */

	/**
	 * Pull raw data from hardware
	 */
	virtual void pull();

	/**
	 * Decode the data at src.
   	 */
	virtual Data* decode();

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
	virtual void getDataFromBuffer();

	/**
	 * Return the data in buffer from startIdx to endIdx
	 * @param startIdx, endIdx
	 */
	@Overload
	virtual void getDataFromBuffer(int startIdx, int endIdx);

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
	 * Constructor for Hardware Interface
	 * @param bufferSize, pullFrequency, policy, hardwareID
	 */
	virtual HwInterface(int bufferSize, int pullFrequency, int policy, int hardwareID);

	/**
	 * Destructor
	 */
	virtual ~HwInterface();

};


#endif 


/* HWINTERFACE_H_ */
