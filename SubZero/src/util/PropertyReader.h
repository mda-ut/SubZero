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
#include <map>

#include <Logger.h>
#include "Properties.h"

/**
 * @brief The PropertyReader class is analogous to the Java Properties class.  Properties are loaded from a file and each property is delimited by a new line.  Each line has the following format:
 * propertyName = value
 * Where each property name is case sensitive.  Values are always interpreted as std::strings and it is up to the caller to convert to another primitive datatype if desired.  If a property is not found, its corresponding value will be an empty string.
 */
class PropertyReader {

private:
    Logger* logger = new Logger("PropertyReader");

protected:
    std::ifstream ifstream;
    std::string filePath;

    /**
     * @brief loadLine Parses the line and attempts to extract out a property-value pair.  This function can be overridden by inheriting classes.
     * @param inputLine String to be parsed
     * @return a std::pair<String, String> to be mapped into the Properties class, and returns NULL if no pair could be extracted
     */
    std::pair<std::string, std::string> loadLine(std::string inputLine);

public:
    /**
     * @brief PropertyReader Constructor that takes in the file path to the properties file
     * @param filePath Path to the properties file
     */
    PropertyReader(std::string filePath);

    virtual ~PropertyReader();

    /**
     * @brief load Opens the properties file and loads the values
     * @return A new Properties instance containing the loaded properties
     */
    Properties* load();

    /**
     * @brief setFilePath Sets the file path to the properties file
     * @param newFilePath New file path for the properties file
     */
    void setFilePath(std::string newFilePath);

};



#endif /* PROPERTYREADER_H_ */
