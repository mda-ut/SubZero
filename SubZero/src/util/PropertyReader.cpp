/*
 * PropertyReader.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: zackage
 */

#include "PropertyReader.h"

std::pair<std::string, std::string> PropertyReader::loadLine(std::string inputLine) {
    std::pair<std::string, std::string> loadedPair("EMPTY", "");
    if (inputLine.find("#") == 0) {
        // Ignore comments
        return loadedPair;
    }
    if (inputLine == "") {
        // Ignore blank lines
        return loadedPair;
    }
    std::size_t delimiterPosition = inputLine.find("=");    //TODO: Replace string literal with a member variable
    if (delimiterPosition == std::string::npos) {
        logger->warn("No \"=\" found in line: " + inputLine);
    } else if (delimiterPosition < 2) {
        logger->error("Invalid property name found in line: " + inputLine);
    } else if (delimiterPosition > inputLine.length() - 1) {
        logger->error("Invalid property value found in line: " + inputLine);
    } else {
        //TODO: Find a way to trim white space
        // Check for two spaces around "="
        if (inputLine[delimiterPosition - 1] != ' ') {
            logger->warn("Missing space before \"=\" in line: " + inputLine);
        }
        if (inputLine[delimiterPosition + 1] != ' ') {
            logger->warn("Missing space after \"=\" in line: " + inputLine);
        }
        // Right now force format of variableName = value
        std::string propertyName = inputLine.substr(0, delimiterPosition - 1);
        std::string value = inputLine.substr (delimiterPosition + 2);
        // Create the map pair
        loadedPair = std::make_pair(propertyName, value);
        logger->info("Mapped " + value + " to " + propertyName);
        return loadedPair;
    }
    return loadedPair;
}

Properties* PropertyReader::load() {
    logger->trace("Opening file: " + filePath);
    if(ifstream.is_open()) {
        logger->info("File already open: " + filePath);
        ifstream.close();
        logger->trace("File closed: " + filePath);
    }

    ifstream.open(filePath);

    // If we couldn't open the input file stream for reading
    if (!ifstream) {
        // Error occured opening file exit
        logger->error("File could not be opened: " + filePath);
        return nullptr;
    } else {
        logger->info("File opened: " + filePath);
    }

    // Iterate through the file to find all properties
    logger->info("Loading properties file...");
    std::map<std::string, std::string> loadedValues;
    while (ifstream) {
        std::string inputLine;
        getline(ifstream, inputLine);
        std::pair<std::string, std::string> loadedPair = loadLine(inputLine);
        if (loadedPair.first == "EMPTY") {
            continue;
        }
        loadedValues.insert(loadLine(inputLine));
    }
    logger->debug("Loaded " + std::to_string(loadedValues.size()) + " properties successfully");
    return new Properties(loadedValues);
}

PropertyReader::~PropertyReader() {
    if(ifstream.is_open()) {
        ifstream.close();
        logger->trace("File closed: " + filePath);
    }
    logger->trace("Property reader deleted");
    delete logger;
}

PropertyReader::PropertyReader(std::string filePath){
    this->filePath = filePath;
}

void PropertyReader::setFilePath(std::string newFilePath){
    filePath = newFilePath;
}
