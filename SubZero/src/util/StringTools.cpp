/*
 * StringTools.cpp
 *
 *  Created on: May 9, 2015
 *      Author: ahsueh1996
 */

#include "StringTools.h"

std::string StringTools::intToStr(int value,int pad) {
	std::string result = "";
    int numberOfDigits =0;
	int onesDigit = 0;
	do {
		onesDigit = value % 10;
		if (onesDigit == 0)
			result = "0" + result;
		else if (onesDigit == 1)
			result = "1" + result;
		else if (onesDigit == 2)
			result = "2" + result;
		else if (onesDigit == 3)
			result = "3" + result;
		else if (onesDigit == 4)
			result = "4" + result;
		else if (onesDigit == 5)
			result = "5" + result;
		else if (onesDigit == 6)
			result = "6" + result;
		else if (onesDigit == 7)
			result = "7" + result;
		else if (onesDigit == 8)
			result = "8" + result;
		else if (onesDigit == 9)
			result = "9" + result;
		value /= 10;
        numberOfDigits++;
	}while (value != 0);
    if (numberOfDigits < pad) {
        int i=0;
        for (i;i<(pad-numberOfDigits);i++)
            result = "0" + result;
    }
	return result;
}
