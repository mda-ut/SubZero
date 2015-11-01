#include "Properties.h"

Properties::Properties(std::map<std::string, std::string> values) {
    this->values = values;
}

std::string Properties::getProperty(std::string propertyName) {
    return values[propertyName];
}
