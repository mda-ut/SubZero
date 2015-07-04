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
	 * FRIEND FUNCS
	 * ==========================================================================
	 */

	/**
	 * Setter for the depth. If a previous value exists, it will
	 * be replaced.
	 *
	 * @param newDepth	double value of depth.
	 */
    void setDepth(int newDepth);

	/**
	 * Setter for the speed. If a previous value exists, it will
	 * be replaced.
	 *
	 * @param newRoll	double value of speed.
	 */
    void setSpeed(int newSpeed);

	/**
	 * Setter for heading. If a previous value exists, it will
	 * be replaced.
	 *
	 * @param newHeading	double value of heading.
	 */
    void setHeading(int newHeading);

	/* ==========================================================================
	 * CLASS VARS
	 * ==========================================================================
	 */

	/*
	 * Depth, speed, heading vars.
	 */
    int depth, speed, heading;

public:

	/* ==========================================================================
	 * CONSTRUCTOR & DESTRUCTOR
	 * ==========================================================================
	 */

	/**
	 * Constructor for FPGAData.
	 *
	 * @param depth
	 * @param speed
	 * @param heading
	 */
    FPGAData(std::string dataID, int depth, int speed, int heading);

	/**
	 * Destructor stub.
	 */
	virtual ~FPGAData();

	/* ==========================================================================
	 * FPGA MANIPULATION FUNCS
	 * ==========================================================================
	 */

	/**
	 * Getter for the depth.
	 *
	 * @return 	double value of depth.
	 */
    int getDepth();

	/**
	 * Getter for the speed.
	 *
	 * @return 	double value of speed.
	 */
    int getSpeed();

    /**
	 * Getter for heading. Heading refers to? Ask Electronics
	 *
	 * @return 	double value of heading.
	 */
    int getHeading();

};

#endif /* FPGADATA_H_ */
