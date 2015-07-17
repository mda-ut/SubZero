/*
 * StringTools.h
 *
 *  Created on: May 9, 2015
 *      Author: ahsueh1996
 */

#ifndef STRINGTOOLS_H_
#define STRINGTOOLS_H_

#include <string>

class StringTools {
public:
	/* ================================================================
	 * STATIC TOOLS
	 * ================================================================
	 */

	/**
	 * Converts integer number to string.
	 *
	 * @param value		integer number.
	 * @return			the string representation of value.
	 */
    static std::string intToStr(int value, int pad=0);
};

#endif /* SRC_UTIL_STRINGTOOLS_H_ */
