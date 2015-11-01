/*
 * Util.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: mda
 */

#include "Util.h"

Util::Util() {
	// TODO Auto-generated constructor stub

}

Util::~Util() {
	// TODO Auto-generated destructor stub
}


std::string Util::getWorkingDirectory( void ) {
   char buff[100];
   getcwd( buff, 100 );
   std::string cwd( buff );
   return cwd;
}
