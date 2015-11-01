#ifndef SIMCAMERAINTERFACE_H_
#define SIMCAMERAINTERFACE_H_

#include "HwInterface.h"
#include "ImgData.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "SimBufferWindow.h"
#include <iostream>


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
class SimCameraInterface : public HwInterface {

private:


   int position;
   SimBufferWindow* bufferWindow;

    Logger* logger = new Logger("CameraInterface");


    /* ==========================================================================
     * 				INTERACTING WITH DATA COMING IN (FROM Camera)
     * ==========================================================================
     * This interface class will be automatically polling and managing
     * the polling process privately within the interface at pollFrequency
     * using the functions below.
     */



    /**
     * Decode the data.
     * @param	data	data to be decoded
     * @return	decoded data in a ImgData format
     */
    virtual ImgData* decode(cv::Mat data);

public:

    /* ==========================================================================
     * 								GETTERS AND SETTERS
     * ==========================================================================
     */

    /**
     * Return the position of the camera.
     * No way to reset camera position without deleting and recreating another
     * CameraInterface. This is to prevent confusion such as data buffer having
     * frames from fixed sources.
     */
    int getPosition();

    /* ==========================================================================
     * 							CONSTRUCTOR AND DESTRUCTOR
     * ==========================================================================
     */

    /**
     * Constructor for Hardware Interface
     * @param	bufferSize	buffer size for the interface
     * @param 	pollFrequencey specifies how frequent video stream is pulled
     * @param	position	camera position
     */
    SimCameraInterface(int position, SimBufferWindow* bufferWindow);

    virtual void init();

    /**
     * Poll raw data from the camera.
     * @return	data polled
     */

    virtual ImgData* poll();

    /**
     * Destructor
     */
    virtual ~SimCameraInterface();
};

#endif
