/*  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../command/Command.h"
#include "../../model/Model.h"

#include <QObject>
#include <QQueue>
#include <QThread>
#include <QMutex>

class Controller : public QObject {
	//QT Macro required whenever you deal with signals, slots or properties
    Q_OBJECT

	public:	 
        /**
         * General QThread for the constructor and destructor - see http://doc.qt.io/qt-5/qthread.html
         */
        QThread queueThread;

        /**
         * Empty Constructor
         */
        Controller(void);

		/**
        * Model Constructor
		*
		* @param vector containing the models
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

        /**
         * Starts our Controller
         */
        void initialize(void);
		
	public slots:
		/**
		 * Handles the results from the ControllerThread
		 */
		void cTHandleResults(const QString &);
		
	signals:
		/**
		 * Tells the ControllerThread to begin 
		 */
        void beginCT(const QString &);

	private:
		/**
		* A List of commands that the view tells us to complete
		*/
		QQueue <class Command* > commandList;
        QMutex mutex;
};

#endif /* CONTROLLER_H_ */
