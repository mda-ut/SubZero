/*
 * VideoLogger.h
 *
 *  Created on: Jul 2, 2015
 *      Author: ahsueh1996
 */

#ifndef UTIL_VIDEOLOGGER_H_
#define UTIL_VIDEOLOGGER_H_


#include <string>
#include "Logger.h"
#include "PropertyReader.h"
#include "data/ImgData.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "Timer.h"
#include <string>
#include <qdir.h>
#include "Util.h"


/**
 * This class provides a way to write img data to a video file.
 * We will use the filetype specified in the settings file and
 * the poll frequency for the output fps. The method of creating
 * the video file is to save an img sequence to some directory
 * then use ffmpeg's terminal command to make it into a video.
 * Alternatively, video editing softwares can also be used to
 * string the img sequence together.
 */
class VideoLogger {
private:

    /**
     * ========================================================
     * CLASS VARS
     * ========================================================
     */

    /*
     * We will use the string logger to record/report information
     * during runtime.
     */
    Logger* logger;

    /*
     * -1 = video writer failed to open, aborts attempts to use
     * the write function.
     */
    int error;

    /*
     * iterates every time write is called--represents the number
     * of frames stored up until now.
     */
    int it;

    /*
     * The number of digits to reserve for the img sequence filename.
     */
    int pad;

    /*
     * The fps value for the final output vid.
     */
    int fps;

    /*
     * Filename of the output vid;
     */
    std::string filename;

    /*
     * Filetype extention string.
     */
    std::string filetype;

    /*
     * The width of the imgs in the sequence.
     */
    int width;

    /*
     * The height of the imgs in the sequence.
     */
    int height;

    Timer timer;
    std::string folderName;

public:

    /**
     * ========================================================
     * CONSTRUCTOR & DESTRUCTOR
     * ========================================================
     */

    /**
     * Constructor
     *
     * @param filename  the name of the avi file, does not include .avi extension
     * @param width     the width of the output video, suggested usage: ImgData.getWidth()
     * @param height    the height of the output video, suggested usage: ImgData.getHeight()
     * @param fps       the frames per second in the output video, if none specified, we use the poll frequency fo hwInterface
     */
    VideoLogger(std::string filename,int width=-1, int height=-1, int fps=-1);

    /**
     * Destructor will destroy the logger and the video writer objs
     */
	virtual ~VideoLogger();

    /**
     * ========================================================
     * MAIN METHOD, WRITE VIDEO FILE FRAME BY FRAME
     * ========================================================
     */

    /**
     * @brief write to the video file extrating the info from
     * ImgData.
     * @param frame ImgData holding the frame to be stored.
     */
    void write(ImgData frame);

    /**
     * @brief write to the video file with a cv mat obj.
     * @param frame to be stored.
     */
    void write(cv::Mat frame);
};

#endif /* UTIL_VIDEOLOGGER_H_ */
