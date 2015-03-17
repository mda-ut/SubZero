/*
 * observer.h
 *
 *  Created on: Feb 14, 2015
 *      Author: edem
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <cv.h>
#include <highgui>

/**
 * This abstract class is informed by the
 * observable class when observable changes state.
 * It then retrieves the data once it is available
 * to read.
 */

class Observer
{
public:
		Observer();

		virtual ~Observer();
		void virtual update(cv::Mat* imgLocFront,cv::Mat* imgLocDown , int* sonarLoc);

};



#endif /* OBSERVER_H_ */
