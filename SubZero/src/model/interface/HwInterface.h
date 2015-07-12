/**
 * HwInterface.h
 *
 * Created on: Jan 17, 2015
 * Author: ahsueh1996
 */

#ifndef HWINTERFACE_H_
#define HWINTERFACE_H_

#include "Logger.h"
#include "Data.h"

enum Attributes {
    POWER,
    DEPTH,
    YAW, // relative to the direction the sub is heading
    SPEED,
    MOTOR
};

/**
 * HwInterface is an abstract class responsible for all the I/O interfacing with
 * the hardware. Hardware interface bridges the interaction between a hardware and
 * the software system downstream.
 *
 * From the hardware, the data is polled at the
 * specified sampling rate then decoded into a format (as defined in Data.h) that
 * can be directly used by the rest of the software system. The decoded data is
 * temporarily stored in a buffer.
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
private:
    Logger* logger = new Logger("HwInterface");

public:

    /* ==========================================================================
     * 							CONSTRUCTOR AND DESTRUCTOR
     * ==========================================================================
     */

    /**
     * Constructor for Hardware Interface
     */
    HwInterface();

    /**
     * Destructor
     */
    virtual ~HwInterface();


    virtual void init() = 0;

    /**
     * Poll raw data from the hardware.
     */
    virtual Data* poll() = 0;

};


#endif


/* HWINTERFACE_H_ */
