/*  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../command/Command.h"
#include <QObject>
#include <QQueue>

class Controller : public QObject {
	public:
		/**
		 * Constructor
		 */
		Controller();

		/**
		 * Destructor
		 */
		virtual ~Controller();

		/**
		 * Adds a new Command to our queue
		 *
		 * @param newCommand - the Command pointer to be added to queue
		 */
		void addCommandToQueue(Command *newCommand);

		/**
		 * Clears all Commands from our queue
		 */
		void clearQueue(void);

		/**
		 * Displays the Current commandList
		 */
		void displayCommandList(void);

		/**
		 * Cleans the queue; forces the last task to finish, then kills the sub
		 */
		void killAll(void);

	private:
		/**
		* A List of commands that the view tells us to complete
		*/
		QQueue <class Command* > commandList;
};

#endif /* CONTROLLER_H_ */
