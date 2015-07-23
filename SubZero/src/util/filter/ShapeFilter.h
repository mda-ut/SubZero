#ifndef SHAPEFILTER_H
#define SHAPEFILTER_H
#include "Filter.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "Logger.h"

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
     *              2 = circle
     * @param amount = number of shapes to look for (1-N)
     */
    ShapeFilter(int shape, int amount);

    virtual ~ShapeFilter();

    /**
     * Filters and looks for shape
     * Works best when passed in an binary image (black/white)
     * @param data = imgData that contains the shape to look for
     * @returns 0 if successful, 1 if failure
     */
    bool filter(Data* data);

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

    /**
     * Bypassing usage of states; for testing purposes
     * Finds rectangles
     * You can get the rectangles found by calling getRect()
     * @param img to filter
     * @return true if rectangle is found
     */
    bool findRect(cv::Mat img);

    /**
     * Bypassing usage of states; for testing purposes
     * Finds circles
     * Need to call getCenter() and getRad() to get circle info
     * @param img to filter
     * @return true if circle is found
     */
    bool findCirc(cv::Mat img);

    /**
     * Returns the center of the biggest mass
     * Although it returns a vector, there will only be one elemnt in it
     * This is to simplify null checking
     * @return a vector of one Point2f; the center of the biggest mass
     */
    static std::vector<cv::Point2f> findMassCenter(cv::Mat img);
    /**
     * Returns the center of the biggest mass
     * Although it returns a vector, there will only be one elemnt in it
     * This is to simplify null checking
     * @return a vector of one Point2f; the center of the biggest mass
     */
    static std::vector<cv::Point2f> findMassCenter(Data* data);

    /**
     * Gets a vector of centers
     * The returned vector is guaranteed to be the same size as the one from getRad()
     * The index of both vectors refer to the same circle
     * @return a vector of points of centers of found circles
     */
    std::vector<cv::Point2f> getCenter();

    /**
     * Gets a vector of radius'
     * The returned vector is guaranteed to be the same size as the one from getCcenter()
     * @return a vector of radiuses of found circles
     */
    std::vector<float> getRad();

private:
    int shape;              //shape to look for
    unsigned int max;

    ///rectangles
    std::vector<cv::RotatedRect> rektangles;    //bounding box

    ///circles
    std::vector<float> radius;
    std::vector<cv::Point2f> center;

    Logger* logger = new Logger("ShapeFilter");
    bool debug = true;
    void print(int i);
    void println(std::string s);

};

#endif // SHAPEFILTER_H
