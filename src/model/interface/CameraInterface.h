/**
 * CameraInterface.h
 *
 * Created on: Jan 17, 2015
 * Author: ahsueh1996
 */

#ifndef CAMERAINTERFACE_H_
#define CAMERAINTERFACE_H_

#include "HwInterface.h"
#include "ImgData.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "VideoLogger.h"

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


   int position;

    Logger* logger = new Logger("CameraInterface");
    VideoLogger* vl = 0;

    cv::VideoCapture camStream;

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
    CameraInterface(int position);

    virtual void init();

    /**
     * Poll raw data from the camera.
     * @return	data polled
     */

    virtual ImgData* poll();

    /**
     * Destructor
     */
    virtual ~CameraInterface();
};

#endif
