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
 * FPGA data in 3 main doubles: depth, roll, and heading. This
 * class will allow observers to get the doubles and perform
 * algorithm off them. It will not serve as a relay to send
 * commands to the FPGA thus, much like ImgData, the setters
 * are reserved for privileged classes.
 */
class FPGAData: public Data {

public:

	/* ==========================================================================
	 * FPGA MANIPULATION FUNCS
	 * ==========================================================================
	 */

	/**
	 * Getter for the depth.
	 *
	 * @return double value of depth.
	 */
	double getDepth();

	/**
	 * Getter for the roll.
	 *
	 * @return double value of roll.
	 */
	double getRoll();

	/*
	 * Getter for heading. Heading refers to? Ask Electronics
	 *
	 * @return double value of heading.
	 */
	double getHeading();

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */

	/**
	 * The = operator overload that will complete a deep copy of the
	 * right hand side operator and return it.
	 */
	FPGAData* operator =(FPGAData* arg);

private:

	/* ==========================================================================
	 * FRIEND FUNCS
	 * ==========================================================================
	 */

	/**
	 * Constructor for FPGAData.
	 *
	 * @param depth
	 * @param roll
	 * @param heading
	 */
	void FPGAData(double depth, double roll, double heading);

	/**
	 * Destructor stub.
	 */
	virtual ~FPGAData();

	/**
	 * Setter for the depth. If a previous value exists, it will
	 * be replaced.
	 *
	 * @param double value of depth.
	 */
	void setDepth(double newDepth);

	/**
	 * Setter for the roll. If a previous value exists, it will
	 * be replaced.
	 *
	 * @param double value of roll.
	 */
	void setRoll(double newRoll);

	/**
	 * Setter for heading. If a previous value exists, it will
	 * be replaced.
	 *
	 * @param double value of heading.
	 */
	void setHeading(double newHeading);

	/**
	 * Depth, roll, heading vars.
	 */
	double depth, roll, heading;
};

#endif /* FPGADATA_H_ */
