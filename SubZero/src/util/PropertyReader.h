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
    std::map<std::string, std::string> values;

    void loadLine(std::string inputLine);

public:
    /**
     * @brief PropertyReader Constructor that takes in the file path to the properties file
     * @param filePath Path to the properties file
     */
    PropertyReader(std::string filePath);

	virtual ~PropertyReader();

    /**
     * @brief load Opens the properties file and loads the values
     */
    void load();

    /**
     * @brief getProperty Returns the value corresponding to the property name
     * @param propertyName Case sensitive property name found in the properties file
     * @return Returns the corresponding value as a std::string and returns an empty string if property cannot be found
     */
	std::string getProperty(std::string propertyName);

    /**
     * @brief setFilePath Sets the file path to the properties file
     * @param newFilePath New file path for the properties file
     */
    void setFilePath(std::string newFilePath);

};



#endif /* PROPERTYREADER_H_ */
