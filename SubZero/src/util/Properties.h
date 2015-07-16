#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include <string>
#include <map>

class Properties {
private:
    std::map<std::string, std::string> values;

public:
    Properties(std::map<std::string, std::string> values);

    /**
     * @brief getProperty Returns the value corresponding to the property name
     * @param propertyName Case sensitive property name found in the properties file
     * @return Returns the corresponding value as a std::string and returns an empty string if property cannot be found
     */
    std::string getProperty(std::string propertyName);
};

#endif // PROPERTIES_H_
