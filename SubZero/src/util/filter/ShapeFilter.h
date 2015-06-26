#ifndef SHAPEFILTER_H
#define SHAPEFILTER_H
#include "Filter.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

/**
 * Post processing filter to look for shapes
 * Works best with binary image (black/white) as input
 * Currently only working for rectangles
 */
class ShapeFilter : public Filter
{
public:
    /**
     * Post processing filter to filter for shapes
     * @param shape = id of the shape you want to filter
     *              1 = rectangle
     */
    ShapeFilter(int shape);

    /**
     * Filters and looks for shape
     * Works best when passed in an binary image (black/white)
     * @param data = imgData that contains the shape to look for
     * @returns 0 if successful, 1 if failure
     */
    int filter(Data* data);

    /**
     * Sets the shape to look for
     * @param shape; 1 = rectangle
     */
    void setShape(int shape);

    /**
     * Gets the bounding box of the rectangle found
     * @return RotatedRect of the rectangle
     */
    cv::RotatedRect* getRect();

    bool findRect(cv::Mat* img);
private:
    int shape;              //shape to look for
    cv::RotatedRect* rektangle;  //bounding box of rectangle

    //std::vector<std::vector<cv::Point> > *contours;
    //std::vector<cv::Vec4i> hierarchy;

};

#endif // SHAPEFILTER_H
