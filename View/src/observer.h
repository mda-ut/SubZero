/*
 * observer.h
 *
 *  Created on: Feb 14, 2015
 *      Author: edem
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

/*
 * This abstract class is informed by the
 * observable class when observable changes state.
 * It then retrieves the data once it is available
 * to read.
 */

class Observer
{
public:
		Observer();

		bool freeToRead();
		void readState();

	/* method of response to observable remains
	undetermined, as does size of imgData
	int[][] imgData;
	int sonarStre; */

		virtual ~Observer();

};



#endif /* OBSERVER_H_ */
