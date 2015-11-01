/*
 * Util.h
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <unistd.h>

class Util {
public:
	Util();
	virtual ~Util();

    /**
     * Gets the Working Directory
     * @return A string of the working directory
     */
    static std::string getWorkingDirectory( void );
};

#endif /* UTIL_H_ */
