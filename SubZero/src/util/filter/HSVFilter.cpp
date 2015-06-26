/**
  * HSVFilter.cpp
  * Created on: June 19, 2015
  * Author: James534
  */
#include "HSVFilter.h"

//using namespace cv;
HSVFilter::HSVFilter(){
    this->setID("HSV");
}

HSVFilter::HSVFilter(int lowH, int highH, int lowS, int highS, int lowV, int highV){
    this->setValues(lowH, highH, lowS, highS, lowV, highV);
    this->setID("HSV");
}

int HSVFilter::filter(Data *data){
    // check for whether the input is of the correct type.      From Albert
    ImgData* imgData = dynamic_cast<ImgData*>(data);
    if (imgData == 0) {
        // track the error and return error
        this->track(data,this->filterID,1,1);
        return 1;
    }
    cv::Mat* mat = imgData->getImg();
    cv::Mat imgHSV;
    cv::Mat* imgThresh = new cv::Mat(mat->clone());

    cv::cvtColor(*mat, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

    cv::inRange(imgHSV, cv::Scalar(this->lowH, this->lowS, this->lowV),
            cv::Scalar(this->highH, this->highS, this->highV), *imgThresh); //Threshold the image

    //morphological opening (remove small objects from the foreground)
    cv::erode(*imgThresh, *imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::dilate(*imgThresh, *imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    //morphological closing (fill small holes in the foreground)
    cv::dilate(*imgThresh, *imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::erode(*imgThresh, *imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    imgData->setImg(imgThresh);
    return 0;
}

cv::Mat* HSVFilter::filter(cv::Mat* mat){
    cv::Mat imgHSV;
    cv::Mat* imgThresh = new cv::Mat(*mat);

    cv::cvtColor(*mat, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

    cv::inRange(imgHSV, cv::Scalar(this->lowH, this->lowS, this->lowV),
            cv::Scalar(this->highH, this->highS, this->highV), *imgThresh); //Threshold the image

    //morphological opening (remove small objects from the foreground)
    cv::erode(*imgThresh, *imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::dilate(*imgThresh, *imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    //morphological closing (fill small holes in the foreground)
    cv::dilate(*imgThresh, *imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::erode(*imgThresh, *imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    return imgThresh;
}

void HSVFilter::setValues(int lowH, int highH, int lowS, int highS, int lowV, int highV){
    this->lowH = lowH;
    this->highH = highH;
    this->lowS = lowS;
    this->highS = highS;
    this->lowV = lowV;
    this->highV = highV;
}
void HSVFilter::setH(int low, int high){
    this->lowH = low;
    this->highH = high;
}
void HSVFilter::setS(int low, int high){
    this->lowS = low;
    this->highS = high;
}
void HSVFilter::setV(int low, int high){
    this->lowV = low;
    this->highV = high;
}
