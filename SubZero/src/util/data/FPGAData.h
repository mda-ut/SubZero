/*
 * FPGAData.h
 *
 *  Created on: Mar 29, 2015
 *      Author: ahsueh1996
 */

#ifndef FPGADATA_H_
#define FPGADATA_H_
#include "Data.h"

/**
 * Wrapper class for data from the FPGA. This class will store
 * FPGA data in 3 main doubles: depth, speed, and heading. This
 * class will allow observers to get the doubles and perform
 * algorithm off them. It will not serve as a relay to send
 * commands to the FPGA thus, much like ImgData, the setters
 * are reserved for privileged classes.
 */
class FPGAData: public Data {

	/*	=========================================================================
	 *	FRIEND CLASSES
	 *	=========================================================================
	 */
	friend class Filter;
	friend class HwInterface;

private:

	/* ==========================================================================
	 * CLASS VARS
	 * ==========================================================================
	 */

	/*
	 * Depth, speed, heading vars.
	 */
    int power, yaw, depth;
public:

	/* ==========================================================================
	 * CONSTRUCTOR & DESTRUCTOR
	 * ==========================================================================
	 */

	/**
	 * Constructor for FPGAData.
	 *
     * @param power
     * @param yaw
     * @param depth
	 */
    FPGAData(std::string dataID, int power, int yaw, int depth);

	/**
	 * Destructor stub.
	 */
	virtual ~FPGAData();

	/* ==========================================================================
     * FPGA GETTER FUNCS
	 * ==========================================================================
	 */

	/**
     * Getter for the power status.
	 *
     * @return 	int vale. 1 if power on, 0 if power off
	 */
    int getPower();

	/**
     * Getter for the yaw
	 *
     * @return 	int value of yaw, in degrees
	 */
    int getYaw();

    /**
     * Getter for depth
	 *
     * @return 	int value of depth, in "cm"
	 */
    int getDepth();

};

#endif /* FPGADATA_H_ */
