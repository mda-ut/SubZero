
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
static int counter=0;
void CameraInterface::poll() {
    //logger->trace("retrieving raw " + std::to_string(counter));
    cv::Mat raw;
    //Older version of OpenCV (tested on Alb's laptop setting)
    // IplImage* raw = cvQueryFrame(this->camStream);
    // cv::cvarrToMat(raw, true, true, 0);

    //New version of OpenCV (not yet tested)
    if (camStream.isOpened()) {
        camStream.read(raw);
    }
    Data* decoded = this->decode(raw);

    this->storeToBuffer(decoded);
}

/**
 * Decode the data.
 * @param	data	data to be decoded
 * @return	decoded data in a ImgData format
 */
ImgData* CameraInterface::decode(cv::Mat data) {
    //logger->trace("inserted image " + std::to_string(counter++));
    cv::cvtColor(data, data, CV_BGR2RGB);
    ImgData* decoded = new ImgData("raw", data);
    return decoded;
}

/* ==========================================================================
 * 								GETTERS AND SETTERS
 * ==========================================================================
 */

int CameraInterface::getPosition(){
    return this->position;
}

/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */


CameraInterface::CameraInterface(int bufferSize, int pollFrequency, int position) : HwInterface(bufferSize, pollFrequency) {
    this->position = position;
    //this->camStream = new cv::VideoCapture(this->position);
    // this->camStream = cvCaptureFromCAM(this->position);
}

void CameraInterface::init(){
    // thread for reading and polling camera input
    std::cout <<"initialized"<<std::endl;

    camStream.open(position);
    camStream.set(CV_CAP_PROP_CONVERT_RGB, true);
    executing = true;
    readThreads.push_back(std::thread(&CameraInterface::in, this));
}

CameraInterface::~CameraInterface() {
    delete logger;
    executing = false;
    for(auto& t: readThreads) {t.join();}

    // clears the queue
    while ( ! decodedBuffer.empty()) {
        delete decodedBuffer.front();
        decodedBuffer.pop();
    }

    camStream.release();
}

