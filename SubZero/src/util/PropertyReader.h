/*
 * PropertyReader.h
 *
 *  Created on: Jun 14, 2015
 *      Author: zackage
 */

#ifndef PROPERTYREADER_H_
#define PROPERTYREADER_H_

#include <string>
#include <fstream>
#include <iostream>

class PropertyReader{

private:
    std::ifstream inFileStream;

	std::string getValueByName(std::string wantedName, std::string tryingLine);

public:
	PropertyReader(std::string propertyFilePath);
	virtual ~PropertyReader();
	std::string getProperty(std::string propertyName);
	void changeFilePath(std::string newFilePath);
};



#endif /* PROPERTYREADER_H_ */
