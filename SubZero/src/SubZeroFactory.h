/*
 * SubZeroFactory.h
 *
 *  Created on: May 25, 2015
 *      Author: carl
 */

#ifndef SUBZEROFACTORY_H_
#define SUBZEROFACTORY_H_

#include "Properties.h"
#include "Logger.h"
#include "SubZero.h"

class Stage;

//jon says to move inside class
enum SubType {GUI, SIM, AUT};

class SubZeroFactory {
private:
    Logger* logger =  new Logger("SubZeroFactory");
    Stage* stage;
    Properties* settings;

public:
    SubZeroFactory(Properties* settings);
	virtual ~SubZeroFactory();
    void setStage(Stage* newStage);

    SubZero* makeSubZero(std::string subType);



};

#endif /* SUBZEROFACTORY_H_ */
