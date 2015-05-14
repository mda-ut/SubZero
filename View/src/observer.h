#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <cv.h>
#include <highgui.h>

/**
 * This abstract class is informed by the
 * observable class when observable changes state.
 * It then retrieves the data once it is available
 * to read. It's only purpose is to handle the
 * observer pattern in the name of modularity.
 */

class Observer
{
public:
        Observer();

        /** The update function updates each view uniquely
         * Called by observable to notify observer of a change in
         * state. Receives pointers to the latests data
         * @param 	imgLocFront	 Pointer to the matrix holding
         * 			image pixel data for the front camera.
         * @param 	imgLocDown 	Pointer to the matrix holding
         * 			image pixel data for the downward camera
         * @param	sonarLoc 	Pointer to latest sonar strength data
         */

        virtual void update(cv::Mat* imgLocFront,cv::Mat* imgLocDown , int* sonarLoc) = 0;

};



#endif /* OBSERVER_H_ */
