
/*
 * CameraInterface.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "CameraInterface.h"
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
ImgData* CameraInterface::poll() {
    ImgData* new_data;
    cv::Mat raw;
    bool readSuccess = false;
    // New version of OpenCV
    if (!camStream.isOpened()) {
        logger->debug("Camera stream is not opened");
    } else if (!signal_quit){
        readSuccess = camStream.read(raw);
    }
    if (readSuccess) {
        logger->trace("Read successful");
        new_data = decode(raw);
    } else {
        logger->error("Camera stream failed to read image");
        cv::Mat temp = cv::Mat::zeros(640, 480, CV_8UC3);
        new_data = new ImgData("raw", temp);
        logger->debug("Inserting an artifical blank image");
    }
    if (signal_quit) {
        logger->trace("Quit signal detected");
        if (!fpga_initialized) {
            // Don't need to wait for fpga, quit now
            exit(0);
        }
    }
    return new_data;
}

/**
 * Decode the data.
 * @param	data	data to be decoded
 * @return	decoded data in a ImgData format
 */
ImgData* CameraInterface::decode(cv::Mat data) {
    if (data.cols <= 0)
        data = cv::Mat::zeros(640, 480, CV_8UC3);
    vl->write(data);
    cv::cvtColor(data, data, cv::COLOR_BGR2RGB);
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


CameraInterface::CameraInterface(int position) {
    this->position = position;
}

void CameraInterface::init() {
    // thread for reading and polling camera input
    logger->info("Initializing");
    logger->info("Opening video capture stream at position " + std::to_string(position));
    if (!camStream.open(position)) {
        logger->error("Failed to open video capture stream, exiting now. Make sure camera(s) are plugged in.");
	//        exit(0);
    }
    if (position == 1) {
        vl = new VideoLogger("One", 640, 480, 30);
    } else {
        vl = new VideoLogger("Two", 640, 480, 30);
    }
}

CameraInterface::~CameraInterface() {
    logger->trace("CameraInterface deleted");
    delete logger;
    delete vl;
}

