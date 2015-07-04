/*  Created on: Jan 7, 2015
 *      Author: mda
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_


#include <QObject>
#include <QQueue>
#include <QThread>
#include <QMutex>
#include <vector>
#include "Task.h"
#include "Model.h"
#include "View.h"
#include "ControllerThread.h"
#include "Logger.h"
#include "TaskFactory.h"

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
        Controller();

		/**
        * Model Constructor
		*
        * @param model - the vector containing the models
		*/
        Controller(std::vector <Model*> models, View* view);

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
         * Initializes our Controller
         */
        void initialize(void);

        /**
         * Returns controller's current running state;
         */
        static bool isRunning();
		
	public slots:
		/**
		 * Handles the results from the ControllerThread
		 */
        void finished(const QString &s);

        /**
         * Handles the button click for toggling power
         */
        void handlePowerButtonToggled(void);

        /**
         * Handles the button click for startup sequence
         */
        void handleMotorButtonClick(void);

        /**
         * Handles the button click for moving left
         */
        void handleMoveLeftButtonClick(void);

        /**
         * Handles the button click for moving right
         */
        void handleMoveRightButtonClick(void);

        /**
         * Handles the button click for moving forward
         */
        void handleMoveForwardButtonClick(void);

        /**
         * Handles the button click for moving backward
         */
        void handleMoveBackwardButtonClick(void);

        /**
         * Handles the button click for stopping the sub
         */
        void handleStopButtonClick();

        /**
         * Handles the button click for sinking
         */
        void handleSinkButtonClick(void);

        /**
         * Handles the button click for rising
         */
        void handleRiseButtonClick(void);

        void handleGateTaskClick();

        void handlePathTaskClick();

        /**
         * Cleans the queue; forces the last task to finish, then kills the sub
         */
        void killAll(void);

        /**
         * Displays the Current taskList
         */
        //void displayTaskList(void);


signals:
		/**
		 * Tells the ControllerThread to begin 
		 */
        void beginCT(const QString &s);

	private:
        Logger* logger = new Logger("Controller");

        ControllerThread *cT;

		/**
        * A Queue of commands View tells us to complete
		*/
        QQueue <class Task* >* taskList;

        /**
         * A mutex lock that will make our writes thread safe.
         */
        QMutex mutex;


        std::vector<Model*> models;
        View* view;

        static bool running;
        int targetYaw;
        int targetDepth;
};

#endif /* CONTROLLER_H_ */
