/**
  * HSVFilter.h
  * Created on: June 19, 2015
  * Author: James534
  */

#ifndef HSVFILTER_H
#define HSVFILTER_H

#include "Filter.h"
#include <opencv2/imgproc.hpp>

/**
 * The HSV Filter allows filtering of Hue, Saturation, Value
 * Uses Opencv's built-in HSV filter, along with noise filtering functions
 */
class HSVFilter : public Filter{
public:

    /* ==================================================
     * Constructors
     * ==================================================
     */
    /**
     * Creates an HSV Filter using the default HSV static variables. Set up the filter values by the set___ functions
     */
    HSVFilter();

    /**
     * HSVFilter with all the parameters specified
     * @param lowH  = lower bound of Hue
     * @param highH = upper bound of Hue
     * @param lowS  = lower bound of Saturation
     * @param highS = upper bound of Saturation
     * @param lowV  = lower bound of Value
     * @param highV = upper bound of Value
     */
    HSVFilter(int lowH, int highH, int lowS, int highS, int lowV, int highV);


    /**
     * HSVFilter constructor to be used when wanting to copy the filter
     * @param obj = HSVFilter to copy
     */
    //HSVFilter(HSVFilter* obj);

    /**
     * Operator overload
     * @param rhs = HSVFilter to copy
     * @return depp copy of rhs
     */
    //HSVFilter* operator=(HSVFilter rhs);

    /* =================================================
     * Filtering
     * =================================================
     */

    /**
     * Filters the img in the ImgData according to the values specified
     * Replaces the image in _data_ with the filtered image
     * @param data = image data to be processed
     * @return 0, successful filter
     */
    bool filter(Data* data);

    /**
     * Quick and cheap filtering for internal testing
     * Only uses Mats, goes around ImgData
     * @param mat = image to be filtered
     * @return pointer to the filterd mat image
     */
    cv::Mat filter(cv::Mat mat);

    /**
     * Sets the values to be used when filtering
     * @param lowH  = lower bound of Hue
     * @param highH = upper bound of Hue
     * @param lowS  = lower bound of Saturation
     * @param highS = upper bound of Saturation
     * @param lowV  = lower bound of Value
     * @param highV = upper bound of Value
     */
    void setValues(int lowH, int highH, int lowS, int highS, int lowV, int highV);

    /**
     * Sets the upper and lower bound of Hue
     * @param low  = lower bound of Hue
     * @param high = upper bound of Hue
     */
    void setH(int low, int high);

    /**
     * Sets the upper and lower bound of Saturation
     * @param low  = lower bound of Saturation
     * @param high = upper bound of Saturation
     */
    void setS(int low, int high);

    /**
     * Sets the upper and lower bound of Value
     * @param low  = lower bound of Value
     * @param high = upper bound of Value
     */
    void setV(int low, int high);

    static int defaultLowH;
    static int defaultHighH;
    static int defaultLowS;
    static int defaultHighS;
    static int defaultLowV;
    static int defaultHighV;

private:
    //values to be used when filtering
    int lowH, highH, lowS, highS, lowV, highV;
};

#endif // HSVFILTER_H
