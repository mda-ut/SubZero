/*
 * PropertyReader.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: zackage
 */

#include "PropertyReader.h"

void PropertyReader::loadLine(std::string inputLine) {
    std::size_t delimiterPosition = inputLine.find("=");    //TODO: Replace string literal with a member variable
    //TODO: Find a way to trim white space
    std::string propertyName = inputLine.substr(0, delimiterPosition - 1);
    std::string value = inputLine.substr (delimiterPosition + 2);
    // Map the property name to the value
    values[propertyName] = value;
    logger->info("Mapped " + value + " to " + propertyName);
}

void PropertyReader::load() {
    logger->trace("Opening file: " + filePath);
    if(ifstream.is_open()) {
//        logger->info("File already open: " + filePath);
        ifstream.close();
//        logger->trace("File closed: " + filePath);
    }

    ifstream.open(filePath);

    // If we couldn't open the input file stream for reading
    if (!ifstream) {
        // Error occured opening file exit
//        logger->error("File could not be opened: " + filePath);
        return;
    } else {
//        logger->info("File opened: " + filePath);
    }

    // Iterate through the file to find all properties
//    logger->info("Loading properties file...");
    while (ifstream) {
        std::string inputLine;
        getline(ifstream, inputLine);
        //TODO: Ignore comments and blank lines
        if (inputLine == "") {
            continue;
        }
        loadLine(inputLine);
    }
//    logger->debug("Loaded " + std::to_string(values.size()) + " properties successfully");
}

std::string PropertyReader::getProperty(std::string propertyName) {
    return values[propertyName];
}

PropertyReader::~PropertyReader() {
    if(ifstream.is_open()) {
        ifstream.close();
        logger->trace("File closed: " + filePath);
    }
    logger->trace("Property file deleted");
    delete logger;
}

PropertyReader::PropertyReader(std::string filePath){
    this->filePath = filePath;
}

void PropertyReader::setFilePath(std::string newFilePath){
    filePath = newFilePath;
}
