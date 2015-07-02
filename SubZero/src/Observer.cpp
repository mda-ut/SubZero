/*
 * observer.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: edem
 */

#include "Observer.h"

Observer:: Observer(std::vector<Observable*>){


}


Observer::~Observer(){


}

/**
 * Called by observable to notify observer of a change in
 * state. Receives pointers to the latests data
 * @param 	imgLocFront	 Pointer to the matrix holding
 * 			image pixel data for the front camera.
 * @param 	imgLocDown 	Pointer to the matrix holding
 * 			image pixel data for the downward camera
 * @param	sonarLoc 	Pointer to latest sonar strength data
 */

void Observer:: update(int ID){


}
