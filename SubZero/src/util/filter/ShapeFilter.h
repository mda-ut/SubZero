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
     * @param amount = number of shapes to look for (1-N)
     */
    ShapeFilter(int shape, int amount);

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
    std::vector<cv::RotatedRect> getRect();

    bool findRect(cv::Mat img);
    bool findCirc(cv::Mat img);

    /**
     * Gets a vector of centers
     * The returned vector is guaranteed to be the same size as the one from getRad()
     * The index of both vectors refer to the same circle
     * @return
     */
    std::vector<cv::Point2f> getCenter();

    /**
     * Gets a vector of radius'
     * The returned vector is guaranteed to be the same size as the one from getCcenter()
     * @return
     */
    std::vector<float> getRad();

private:
    int shape;              //shape to look for
    int max;
    //rectangles
    std::vector<cv::RotatedRect> rektangles;
    //cv::RotatedRect rektangle;  //bounding box of rectangle

    //circles
    std::vector<float> radius;
    std::vector<cv::Point2f> center;

};

#endif // SHAPEFILTER_H
