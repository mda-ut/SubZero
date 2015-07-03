/*
 * CameraInterface.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "CameraInterface.h"
#include <string>

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

void CameraInterface::poll() {
    cv::Mat raw;
    bool readSuccess = false;
    // New version of OpenCV
    if (!camStream.isOpened()) {
        logger->debug("Camera stream is not opened");
    } else {
        readSuccess = camStream.read(raw);
    }
    if (readSuccess) {
        Data* decoded = decode(raw);
        storeToBuffer(decoded);
    } else {
        logger->error("Camera stream failed to read image");
    }
}

/**
 * Decode the data.
 * @param	data	data to be decoded
 * @return	decoded data in a ImgData format
 */
ImgData* CameraInterface::decode(cv::Mat data) {
    cv::cvtColor(data, data, CV_BGR2RGB);
    ImgData* decoded = new ImgData("raw", data);
    return decoded;
}

/* ==========================================================================
 * 								GETTERS AND SETTERS
 * ==========================================================================
 */

int CameraInterface::getPosition() {
    return position;
}

/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */


CameraInterface::CameraInterface(int bufferSize, int pollFrequency, int position) : HwInterface(bufferSize, pollFrequency) {
    this->position = position;
}

void CameraInterface::init() {
    // thread for reading and polling camera input
    logger->info("Initializing");

    logger->info("Opening Camera Stream at position " + std::to_string(position));
    camStream.open(position);
    //camStream.set(CV_CAP_PROP_CONVERT_RGB, true);
    executing = true;
    logger->info("Starting thread");
    readThreads.push_back(std::thread(&CameraInterface::in, this));
}

CameraInterface::~CameraInterface() {
    executing = false;
    for(auto& t: readThreads) {
        t.join();
    }
    camStream.release();

    // clears the queue
    while (!decodedBuffer.empty()) {
        delete decodedBuffer.front();
        decodedBuffer.pop();
    }

    delete logger;
}
