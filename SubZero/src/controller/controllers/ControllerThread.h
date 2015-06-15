/*
 * ControllerThread.h
 *
 *  Created on: Mar 28, 2015
 *      Author: LuckyChewie
 */

#ifndef CONTROLLERTHREAD_H_
#define CONTROLLERTHREAD_H_

#include <QThread>
#include <QQueue>
#include <QObject>

class ControllerThread : public QObject {
//    	Q_OBJECT
//
//		/**
//		 * Constructs a ControllerThread
//		 *
//		 * @param cL - the QQueue from T~T
//		 */
//    public:
//        ControllerThread();
//        //ControllerThread(QQueue <class Command* > *cL);
//
//	public slots:
//		/**
//		 * Execute the commands on the queue
//		 *
//		 * @param
//		 */
//		void executeCommands(const QString &parameter);
//
//	signals:
//		/**
//		 * Signals the thread that created us that we are finished
//		 *
//		 * @params QString - the string we emit
//		 */
//		void resultReady(const QString &s);
//
//	private:
//    	/**
//    	 * A List of commands that the view tells us to complete
//    	 */
//    	QQueue <class Command* > *commandList;
};

#endif /* CONTROLLERTHREAD_H_ */
