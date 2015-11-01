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
#include <string>
#include <QMutex>
#include "HwInterface.h"
#include "FPGAData.h"
#include "Properties.h"

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

    Logger* logger = new Logger("FPGAInterface");

protected:
    Properties* settings;

    QMutex mutex;

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
    virtual FPGAData* poll();


public:

    /* ==========================================================================
     * 				INTERACTING WITH DATA GOING OUT (TO FPGA)
     * ==========================================================================
     * FPGAInterface provides functions for the Controller to send data/commands/
     * messages to the FPGA.
     */

    /**
     * Give commands to FPGA.
     * @param	attr	attribute to set
     * @param	value	set attribute to this value
     */
    virtual void set(Attributes attr, int value);


    /* ==========================================================================
     * 							CONSTRUCTOR AND DESTRUCTOR
     * ==========================================================================
     */

    /**
     * Constructor for FPGA Interface
     */
    FPGAInterface(Properties* settings);

    virtual void init();

    /**
     * Destructor
     */
    virtual ~FPGAInterface();

};

#endif


/* FPGAINTERFACE_H_ */
