#include "ShapeFilter.h"


ShapeFilter::ShapeFilter(int shape)
{
    rektangle = 0;
    setShape(shape);
    //contours = new std::vector<std::vector<cv::Point> >;
}

bool debug = true;
void print(int i){
    if (debug)
        std::cout<<i;
}

void println(std::string s){
    if (debug)
        std::cout<< s << std::endl;
}

int ShapeFilter::filter(Data *data){
    // check for whether the input is of the correct type.          From Albert
    ImgData* imgData = dynamic_cast<ImgData*>(data);
    if (imgData == 0) {
        // track the error and return error
        this->track(data,this->filterID,1,1);
        return 1;
    }

    if (shape == 1){    //rectangle
        return this->findRect(imgData->getImg());
    }
    return 1;
}

bool ShapeFilter::findRect(cv::Mat* img){
    //getting the contours
    cv::Mat canny;
    std::vector<std::vector<cv::Point> > *contours
            = new std::vector<std::vector<cv::Point> >;
    std::vector<cv::Vec4i> hierarchy;
    cv::Canny(*img, canny, 50, 20, 3);
    cv::findContours(canny, *contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    //searching for rectangles
    int boxesFound = 0;         //constants
    unsigned int minPoints = 6;
    double minArea = 500;
    double maxArea = 500000;
    float lwMin = 1;
    float lwMax = 5;
    double areaMin = 0.6;
    double perimMin = 0.75;
    double perimMax = 1.2;

    for (std::vector<cv::Point> co: *contours){
        //error checking
        if (co.size() < minPoints){
            println("Not enough Points");
            continue;
        }
        double area = cv::contourArea(co);
        if (area < minArea){
            print(area);
            println(" Not enough Area");
            continue;
        }
        if (area > maxArea){
            print(area);
            println(" Too much Area");
            continue;
        }

        CvBox2D rect = cv::minAreaRect(co);
        float angle = rect.angle;
        float length = rect.size.height;
        float width = rect.size.width;
        if (length < width){
            length = rect.size.width;
            width = rect.size.height;
            angle += 90;
        }

        float lw_ratio = length/width;
        if (lw_ratio < lwMin){
            println("LW ratio too small");
            continue;
        }
        if (lw_ratio > lwMax){
            println("LW ratio too big");
            continue;
        }
        double perimneter = cv::arcLength(co, 1);
        double perim_ratio = perimneter/ (2*length+2*width);
        double area_ratio = area/(length*width);
        if (area_ratio < areaMin){
            println("area ratio too small");
            continue;
        }
        if (perim_ratio > perimMax){
            println("area ratio too small");
            continue;
        }
        if (perim_ratio < perimMin){
            println("area ratio too small");
            continue;
        }


        delete rektangle;   //prevent memory leaks, hope it dosnt crash
        rektangle = new cv::RotatedRect(rect);
        println("FOUND");
        boxesFound++;
    }
    return boxesFound != 0;
}

void ShapeFilter::setShape(int shape){
    this->shape = shape;
    if (shape == 0) this->msg = "rect";
}

cv::RotatedRect* ShapeFilter::getRect(){
    return rektangle;
}
