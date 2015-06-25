/**
 * CameraInterface.h
 *
 * Created on: Jan 17, 2015
 * Author: ahsueh1996
 */

#ifndef CAMERAINTERFACE_H_
#define CAMERAINTERFACE_H_

#include "HwInterface.h"
#include "../../util/data/ImgData.h"
// include other camera + image specific classes
// #include "ImageInputProcessor.h"
// #include "ImageFormatter.h"
// #inlcude "CamIntrinsic.h" //stores camera intrinsic parameters

enum CameraPosition {
	FRONT,
	DOWN
};

/**
 * A concrete child of HwInterface that deals specifically with the camera.
 *
 * CameraInterface is responsible for:
 * 		1. Dealing with the data coming from Camera: poll->decode
 * 		2. Managing its private buffer: store the new, delete the old
 *
 * @version	0.0
 * @since	Jan 17 2015
 */
class CameraInterface : public HwInterface {

private:

	/* ==========================================================================
	 * 				INTERACTING WITH DATA COMING IN (FROM Camera)
	 * ==========================================================================
	 * This interface class will be automatically polling and managing
	 * the polling process privately within the interface at pollFrequency
	 * using the functions below.
	 */

	/**
	 * Poll raw data from the camera.
	 * @return	data polled
	 */
	virtual void poll();

	/**
	 * Decode the data.
	 * @param	data	data to be decoded
	 * @return	decoded data in a ImgData format
   	 */
	virtual ImgData* decode(cv::Mat* data);

protected:

	/* ==========================================================================
	 * 							MANAGING DATA BUFFER
	 * ==========================================================================
	 * The data buffer will be managed automatically and privately by this class.
	 * These functions are defined and implemented in the root parent class i.e.
	 * in HwInterface.
	 */

	/**
	 * Delete buffer from startIdx to endIdx
	 * @param	stardIdx	start deleting from this index
	 * @param	endIdx	the index of the last data to delete
	 */
	virtual void deleteFromBuffer(int startIdx, int endIdx);

	/**
	  * Store decoded data to buffer.
	  * @param	data	data to be stored to buffer.
	  */
	virtual void storeToBuffer(Data* data);

public:

	/* ==========================================================================
	 * 								GETTERS AND SETTERS
	 * ==========================================================================
	 */

	/**
	 * Return the most recent buffer data.
	 * This function is defined and implemented by the parent class (HwInterface).
	 * @return	Data*	the most recent data in buffer
	 *
	 */
	virtual Data* getDataFromBuffer();

	/**
	 * Return the data in buffer from startIdx to endIdx. Overloading the function
	 * above. (Also implemented in HwInterface.)
	 * @param	startIdx	get data starting at this index
	 * @param	endIdx	index of the last data to get
	 * @return	an array of data
	 */
	//@Overload
	virtual Data* getDataFromBuffer(int startIdx, int endIdx);

	/**
	 * Get the frequency of data polling (polls per second)
	 * @return	polling frequency i.e. sampling rate
	 */
	virtual int getPollFrequency();

	/**
	 * Set the frequency of data polling/polling.
	 * @param	frequency	set polling to this frequency
	 */
	virtual void setPollFrequency(int frequency);

	/**
	 * Get size of buffer.
	 * @return	size of the buffer
	 */
	virtual int getBufferSize();

	/**
	 * Set size of buffer.
	 * @param	bufferSize	reset buffer size to this
	 */
	virtual void setBufferSize(int bufferSize);


	/* ==========================================================================
	 * 							CONSTRUCTOR AND DESTRUCTOR
	 * ==========================================================================
	 */

	/**
	 * Constructor for Hardware Interface
	 * @param	bufferSize	buffer size for the interface
	 * @param 	pullFrequencey specifies how frequent video stream is pulled
	 * @param	policy	specifies the encoding and decoding policy to be used
	 * @param	hardwareID	identifies the hardware this interface interacts with
	 */
	CameraInterface(int bufferSize, int pullFrequency, int policy, int hardwareID);

	/**
	 * Destructor
	 */
	virtual ~CameraInterface();

};

#endif
