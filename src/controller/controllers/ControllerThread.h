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

#include "../task/Task.h"

class ControllerThread : public QObject {
    Q_OBJECT

    public:
        /**
         * Task ControllerThread Constructor
		 *
		 * @param cL - the QQueue from T~T
         * @param mutex - the QMutexd from T~T
		 */
        ControllerThread(QQueue <class Task* > *tL, QMutex *mutex);

        virtual ~ControllerThread();

	public slots:
		/**
         * Execute the tasks on the queue
		 *
         * @param
		 */
        void executeTasks(const QString &parameter);

	signals:
		/**
		 * Signals the thread that created us that we are finished
		 *
		 * @params QString - the string we emit
		 */
		void resultReady(const QString &s);

	private:
        Logger* logger = new Logger("ControllerThread");

        /**
         * A pointer to Controller's Queue of tasks
    	 */
        QQueue <class Task* > *taskList;

        /**
         * A pointer to Controller's mutex lock
         */
        QMutex *mutex;
};

#endif /* CONTROLLERTHREAD_H_ */
