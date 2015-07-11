#ifndef SIMINTERFACE_H
#define SIMINTERFACE_H

#include <thread>
#include <queue>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <queue>

#include "../util/PropertyReader.h"
#include "../util/Logger.h"

class SIMInterface
{
protected:
    Logger* logger;
public:
    SIMInterface();
    virtual ~SIMInterface();
};

#endif // INTERFACE_H
