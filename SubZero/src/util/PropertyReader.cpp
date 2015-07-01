/*
 * PropertyReader.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: zackage
 */

#include "PropertyReader.h"

/* ***************************
 * Private functions
 */

std::string PropertyReader::getValueByName(std::string wantedName, std::string tryingLine){
	std::size_t dividerPosition = tryingLine.find("=");
    std::string tryingName = tryingLine.substr (0, dividerPosition - 1);
    if (tryingName == wantedName)
		return tryingLine.substr (dividerPosition + 2);
	else
		return "Wrong";
}


/* ***************************
 * Public functions
 */

std::string PropertyReader::getProperty(std::string propertyName){
    while (inFileStream)
    {
        // read stuff from the file into a string and print it
        std::string inputString;
        getline(inFileStream, inputString);
        std::string findResult = getValueByName(propertyName,inputString);
        if(findResult != "Wrong")
            return findResult;
    }

    return "Wrong";
}

PropertyReader::~PropertyReader(){
}

PropertyReader::PropertyReader(std::string propertyFilePath){
    inFileStream.open(propertyFilePath);
	// inFileStream->open(propertyFilePath);

	// If we couldn't open the input file stream for reading
    if (!inFileStream)
	{
		// Print an error and exit
		std::cerr << "Uh oh, Sample.dat could not be opened for reading!" << std::endl;
	}
}

void PropertyReader::changeFilePath(std::string newFilePath){
    if(inFileStream.is_open()) {
        inFileStream.close();
    }
    inFileStream.open(newFilePath);
	// inFileStream->open(propertyFilePath);

	// If we couldn't open the input file stream for reading
    if (!inFileStream)
	{
		// Print an error and exit
		std::cerr << "Uh oh, Sample.dat could not be opened for reading!" << std::endl;
	}
}
