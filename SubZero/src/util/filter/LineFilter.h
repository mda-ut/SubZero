/**
  * LineFilter.h
  * Created on: June 19, 2015
  * Author: James534
  */
#ifndef LINEFILTER_H
#define LINEFILTER_H

#include "Filter.h"
#include <opencv2/imgproc.hpp>

/**
 * The Line filter filters the image to look for lines
 * This is best used after the HSV filter
 * Uses Opencv's built in Hough Line Transform
 */
class LineFilter : public Filter
{
public:

    /* ======================================================
     * Constructors
     * ======================================================
     */

    /**
     * Empty line filter, use setMode to set the mode to use
     */
    LineFilter();

    /**
     * Filters an image for lines
     * @param mode; 0 = Standard Hough Line Transform,
     *              1 = Probabilistic Hough Line Transform
     */
    LineFilter(int mode);

    /* =====================================================
     * Filtering
     * =====================================================
     */

    /**
     * Filters the image to look for lines
     * Replaces the mat image in _data_
     * @param data = image data to use
     * @return 0 = success
     */
    int filter(ImgData *data);

    /**
     * Filters the image to look for lines
     * Quicky and dirty method to bypass using ImgData, for testing purposes
     * @param src = mat image to filter
     * @return reference to the filtered image
     */
    cv::Mat* filter(cv::Mat* src);


    /**
     * Sets the mode to use for filtering
     * @param mode; 0 = Standard Hough Line Transform,
     *              1 = Probabilistic Hough Line Transform
     */
    void setMode(int mode);
private:
    //mode to use for filtering
    int mode;
};

#endif // LINEFILTER_H
