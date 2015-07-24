/*
 * VideoLogger.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: ahsueh1996
 */

#include "VideoLogger.h"


VideoLogger::VideoLogger(std::string filename, int width, int height, int fps) {
    logger = new Logger(filename+"-VideoLogging");

    if (fps < 1) {
        PropertyReader* propReader = new PropertyReader("../../SubZero/src/settings/settings.txt");
        Properties* settings = propReader->load();
        this->fps = std::stoi(settings->getProperty("CAM_POLL_FREQUENCY"));
        delete settings;
    } else
        this->fps = fps;

    PropertyReader* videoLoggerPropReader = new PropertyReader("../../SubZero/src/settings/videoLogger.txt");
    Properties* videoSettings = videoLoggerPropReader->load();
    this->pad = std::stoi(videoSettings->getProperty("ZEROPAD"));
    this->filetype = videoSettings->getProperty("FILETYPE");
    delete videoSettings;

    this->it = 0;
    this->filename = filename;
    this->error = 0;

    // make the output directory
    std::system(("mkdir videoLog && cd videoLog && mkdir "+filename).c_str());
}

VideoLogger::~VideoLogger() {
    std::system(("ffmpeg -i \'videoLog/"+filename+"/%0"+StringTools::intToStr(pad)+"d.jpg\' -r "+StringTools::intToStr(fps)+" \'videoLog/"+filename+"/"+filename+".avi\'").c_str());
    logger->close();
}

void VideoLogger::write(ImgData frame) {
    this->write(frame.getImg());
}

void VideoLogger::write(cv::Mat frame) {
    if (error == 0) {
        cv::imwrite("videoLog/testvid/"+StringTools::intToStr(it++,pad)+".jpg",frame);
    }
}
