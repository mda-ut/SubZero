
/*
 * CameraInterface.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "SimCameraInterface.h"
#include <string>
#include "scripts.h"


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
ImgData* SimCameraInterface::poll() {
//    ImgData* new_data;
    cv::Mat raw;
    raw = bufferWindow->getImg(position);
    return decode(raw);
}
/**
 * Decode the data.
 * @param	data	data to be decoded
 * @return	decoded data in a ImgData format
 */
ImgData* SimCameraInterface::decode(cv::Mat data) {
//    cv::cvtColor(data, data, CV_BGR2RGB);
    ImgData* decoded = new ImgData("raw", data);
    return decoded;
}

/* ==========================================================================
 * 								GETTERS AND SETTERS
 * ==========================================================================
 */

int SimCameraInterface::getPosition() {
    return position;
}

/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */


SimCameraInterface::SimCameraInterface(int position, SimBufferWindow* bufferWindow) {
    this->position = position;
    this->bufferWindow = bufferWindow;
}

void SimCameraInterface::init() {
    // thread for reading and polling camera input
    logger->info("Initializing");

}

SimCameraInterface::~SimCameraInterface() {
    logger->trace("SimCameraInterface deleted");
    delete logger;
}

