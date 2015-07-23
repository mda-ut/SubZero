/**
  * LineFilter.h
  * Created on: June 19, 2015
  * Author: James534
  */
#ifndef LINEFILTER_H
#define LINEFILTER_H

#include "Filter.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "Logger.h"

/**
 * The Line filter filters the image to look for lines
 * This is best used after the HSV filter
 * Uses Opencv's built in Hough Line Transform
 */
class LineFilter : public Filter
{
public:

    /* ======================================================
     * Constructor
     * ======================================================
     */

    /**
     * Filters an image for lines
     */
    LineFilter();
    virtual ~LineFilter();

    /* =====================================================
     * Filtering
     * =====================================================
     */

    /**
     * Filters the image to look for lines
     * Replaces the mat image in _data_
     * @param data = image data to use
     * @return 0 = found lines
     */
    bool filter(Data *data);

    /**
     * Filters the image to look for lines
     * Quicky and dirty method to bypass using ImgData, for testing purposes
     * This filteration draws lines
     * @param src = mat image to filter
     * @param mode; 0 = Standard Hough Line Transform,
     *              1 = Probabilistic Hough Line Transform
     * @return reference to the filtered image with lines drawn
     */
    cv::Mat filter(cv::Mat src, int mode);

    /**
     * Returns the slope and intercept value of all the lines detected,
     * were a line is represented by y = mx+b
     * Since you cant have a vector of arrays, it returns a vector of vectors.
     * The iner array can be size 2 or 3
     * Size 2 is just [0] = m, [1] = b
     * Size 3 is [0] = m, [1] = b, [2] = x/y depending on what m is
     * @return a vector of all the lines detected
     */
    std::vector<std::vector<float>> getlineEq();

private:
    //mode to use for filtering
    int mode;
    std::vector<std::vector<float> > linesEq;

    Logger* logger = new Logger("LineFilter");
    bool debug = true;
    void println(std::string s);
    void println(float f);
    void print(std::string s);
    void print(float f);
};

#endif // LINEFILTER_H
