/*  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_


#include <QObject>
#include <QQueue>
#include <QThread>
#include <QMutex>

#include "../task/Task.h"
#include "../../model/Model.h"

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
        * @param model - the vector containing the models
		*/
		Controller(std::vector <Model*> model);

		/**
		 * Destructor
		 */
		virtual ~Controller();

		/**
         * Adds a new Task to our queue
		 *
         * @param newTask - the Task pointer to be added to queue
		 */
        void addTaskToQueue(Task *newTask);

		/**
		 * Clears all Commands from our queue
		 */
		void clearQueue(void);

		/**
         * Displays the Current taskList
		 */
        void displayTaskList(void);

		/**
		 * Cleans the queue; forces the last task to finish, then kills the sub
		 */
		void killAll(void);

        /**
         * Initializes our Controller
         */
        void initialize(void);
		
	public slots:
		/**
		 * Handles the results from the ControllerThread
		 */
        void cTHandleResults(const QString &s);
		
	signals:
		/**
		 * Tells the ControllerThread to begin 
		 */
        void beginCT(const QString &s);

	private:
		/**
        * A Queue of commands View tells us to complete
		*/
        QQueue <class Task* > taskList;

        /**
         * A mutex lock that will make our writes thread safe.
         */
        QMutex mutex;
};

#endif /* CONTROLLER_H_ */
