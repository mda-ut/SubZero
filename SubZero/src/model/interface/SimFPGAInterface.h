/**
 * SimFPGAInterface.h
 *
 * Created on: Jan 17, 2015
 * Author: ahsueh1996
 */

#ifndef SIMFPGAINTERFACE_H_
#define SIMFPGAINTERFACE_H_

#include <thread>
#include <iostream>
#include <string>
#include <QMutex>
#include "FPGAInterface.h"
#include "FPGAData.h"
#include "Properties.h"
#include "SimFPGA.h"

/**
 * A concrete child of HwInterface that deals specifically with the simulated FPGA.
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

class SimFPGAInterface : public FPGAInterface {

private:

    Logger* logger = new Logger("SimFPGAInterface");

protected:
    SimFPGA* simFPGA;

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
    SimFPGAInterface(Properties* settings, SimFPGA* simFPGA);

    virtual void init();

    /**
     * Destructor
     */
    virtual ~SimFPGAInterface();

};

#endif


/* SIMFPGAINTERFACE_H_ */
