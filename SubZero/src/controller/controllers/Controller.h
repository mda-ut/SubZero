/*  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../command/Command.h"
#include "../../model/Model.h"
#include <QObject>
#include <QQueue>
#include <vector>

class Controller : public QObject {
	//QT Macro required whenever you deal with signals, slots or properties
    Q_OBJECT
	
	public:	 
	
		QThread queueThread;
		
		/**
		* Constructor
		*/
		Controller(std::vector <Model*> model);

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
		
	public slots:
		void handleResults(const QString &);
		
	signals:
		void operate(const QString &);

	private:
		/**
		* A List of commands that the view tells us to complete
		*/
		QQueue <class Command* > commandList;
};

#endif /* CONTROLLER_H_ */
