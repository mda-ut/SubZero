/**
 * HwInterface.h
 *
 * Created on: Jan 17, 2015
 * Author: ahsueh1996
 */

#ifndef HWINTERFACE_H_
#define HWINTERFACE_H_

#include "../../util/data/Data.h"
#include <queue>


/**
 * HwInterface is an abstract class responsible for all the I/O interfacing with
 * the hardware. Hardware interface bridges the interaction between a hardware and
 * the software system downstream.
 *
 * From the hardware, the data is polled at the
 * specified sampling rate then decoded into a format (as defined in Data.h) that
 * can be directly used by the rest of the software system. The decoded data is
 * temporary stored in a buffer.
 *
 * This temporary buffer is managed automatically and privately by the interface to
 * ensure that the data stays up-to-date.
 *
 * Commands and data to be sent to the hardware from the software system are first
 * encoded to a format acceptable by the hardware prior to sending.
 *
 * In short the interface is responsible for:
 * 		1. Dealing with the data coming from the hardware: poll->decode
 * 		2. Managing the buffer: store the new stuff, delete the old stuff
 * 		3. Dealing with the data going to the hardware: encode->send
 *
 * @version	0.0
 * @since	Jan 17 2015
 */

class HwInterface {

protected:

    /* ==========================================================================
     * 								CLASS VARIABLES
     * ==========================================================================
     */

    /**
     * Pointer to memory allocated for storing raw (but
     * decoded) data from hardware.
     */
    std::queue<Data> decodedBuffer;

    /**
     * Allocate only enough memory to keep a max of
     * this number of hardware inputs; discard all after that.
     */
    int bufferSize;

    /**
     * Poll data from hardware at this frequency (number of polls per second).
     * A.k.a. sampling rate.
     */
    int pollFrequency;


    /* ==========================================================================
     * 				INTERACTING WITH DATA COMING IN (FROM HARDWARE)
     * ==========================================================================
     * This interface class will be automatically polling and managing
     * the polling process privately within the interface at pollFrequency
     * using the functions below.
     * NOTE: In abstract parent HwInterface, these functions are just placeholders.
     */

    /**
     * Poll raw data from the hardware.
     */
    virtual void poll()=0;

    /**
     * Decode the data.
     * @param	data	data to be decoded
     * @return	decoded data in a format defined in Data.h
     */
    virtual Data* decode();

    /* ==========================================================================
     * 							MANAGING DATA BUFFER
     * ==========================================================================
     * The data buffer will be managed automatically and privately by this class.
     * These functions are defined and implemented in the root parent class i.e. .
     * HwInterface (this class).
     */

    /**
     * Delete buffer from startIdx to endIdx
     */
    virtual void deleteFromBuffer()=0;

    /**
      * Store decoded data to buffer.
      * @param	data	data to be stored to buffer.
      */
    virtual void storeToBuffer(Data* data)=0;

public:

    /* ==========================================================================
     * 				INTERACTING WITH DATA GOING OUT (TO HARDWARE)
     * ==========================================================================
     * The interface provides functions for other classes of the software system
     * to send data/commands/messages to the hardware. These functions are to be
     * implemented by the children. Here they are just placeholders.
     */

    /**
     * Encodes the data to be sent.
     * @param	data	data to be encoded
     * @return	encoded data
     */
 //   virtual void encode();

    /**
     * Send the data.
     * @param	data	data to be sent
     */
  //  virtual void send();


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
    virtual Data* getDataFromBuffer()=0;

    /**
     * Get the frequency of data polling (polls per second)
     * @return	polling frequency i.e. sampling rate
     */
    virtual int getPollFrequency()=0;

    /**
     * Set the frequency of data polling (polls per second)
     * @param	frequency	set polling to this frequency
     */
    virtual void setPollFrequency(int frequency)=0;

    /**
     * Get size of buffer.
     * @return	size of the buffer
     */
    virtual int getBufferSize()=0;

    /**
     * Set size of buffer.
     * @param	bufferSize	reset buffer size to this
     */
    virtual void setBufferSize(int bufferSize)=0;


    /* ==========================================================================
     * 							CONSTRUCTOR AND DESTRUCTOR
     * ==========================================================================
     */

    /**
     * Constructor for Hardware Interface
     * @param	bufferSize	buffer size for the interface
     * @param	pollFrequency	number of polls per second
     */
    HwInterface(int bufferSize, int pollFrequency);

    /**
     * Destructor
     */
    virtual ~HwInterface();

};


#endif


/* HWINTERFACE_H_ */
