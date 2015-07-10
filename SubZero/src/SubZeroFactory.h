/*
 * SubZeroFactory.h
 *
 *  Created on: May 25, 2015
 *      Author: carl
 */

#ifndef SUBZEROFACTORY_H_
#define SUBZEROFACTORY_H_

#include "SubZero.h"
#include "Properties.h"
#include "Logger.h"

//jon says to move inside class
enum SubType {GUI, SIM, AUT};

class SubZeroFactory {
private:
    Logger* logger =  new Logger("SubZeroFactory");
    Stage* stage;

public:
	SubZeroFactory();
	virtual ~SubZeroFactory();
    void setStage(Stage* newStage);

    SubZero* makeSubZero(SubType subType, Properties* settings);



};

#endif /* SUBZEROFACTORY_H_ */
