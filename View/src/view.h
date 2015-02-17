/*
 * view.h
 *
 *  Created on: Feb 15, 2015
 *      Author: edem
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "observer.h"

/* This abstract class inherits observer's
 * functionality and displays the data via use of
 * the qt framework. In addition it receives
 * commands from the user and sends them to the
 * controller to be implemented
 */

class view : public observer
{
public:
		view();

		void moveForward();
		void moveBackward();
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void surface();
		void launchTor();
		void launchGra();
		void changeWinDim();
		void displayWin();
		void toMenu();

		virtual ~view();
};


#endif /* VIEW_H_ */
