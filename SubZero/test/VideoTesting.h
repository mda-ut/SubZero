#ifndef VIDEOTESTING_H
#define VIDEOTESTING_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

#include "../src/util/filter/HSVFilter.h"
#include "../src/util/filter/LineFilter.h"
#include "../src/util/filter/ShapeFilter.h"
#include "../src/util/filter/BlurFilter.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>


/**
 * Video testing is for opening video files and testing with them
 */
class VideoTesting
{
public:
    //VideoTesting(); //default file name is "test.avi"

    /**
     * VideoTesting is for opening video files and running test with them
     * @param fileName = name of the video file to open
     */
    VideoTesting(const std::string fileName);

    /**
     * VideoTesting is for opening video files and running test with them
     * @param deviceID = name of the camera to open, default is 0
     */
    VideoTesting(int deviceID = 0);

    /**
     * Runs the video file at 30 fps
     */
    void run();

    /**
     * @return the next frame in the video
     */
    cv::Mat getNextFrame();

    //cv::Mat getNextCameraFrame();

private:
    cv::VideoCapture cap;
};

#endif // VIDEOTESTING_H
