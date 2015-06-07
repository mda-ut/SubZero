/*
 * ControllerThread.h
 *
 *  Created on: Mar 28, 2015
 *      Author: LuckyChewie
 */

#ifndef CONTROLLERTHREAD_H_
#define CONTROLLERTHREAD_H_

#include <QThread>
#include <QObject>
#include <QQueue>
#include <QMutex>

#include "../command/Command.h"

class ControllerThread : public QObject {
    Q_OBJECT

    public:
        /**
         * Command ControllerThread Constructor
		 *
		 * @param cL - the QQueue from T~T
         * @param mutex - the QMutexd from T~T
		 */
        ControllerThread(QQueue <class Command* > *cL, QMutex *mutex);

	public slots:
		/**
		 * Execute the commands on the queue
		 *
		 * @param 
		 */
        void executeCommands(const QString &parameter);

	signals:
		/**
		 * Signals the thread that created us that we are finished
		 *
		 * @params QString - the string we emit
		 */
		void resultReady(const QString &s);

	private:
        /**
    	 * A List of commands that the view tells us to complete
    	 */
        QQueue <class Command* > *commandList;
        QMutex *mutex;
};

#endif /* CONTROLLERTHREAD_H_ */
