/**
  * HSVFilter.cpp
  * Created on: June 19, 2015
  * Author: James534
  */
#include "HSVFilter.h"

int HSVFilter::defaultLowH = 0;
int HSVFilter::defaultHighH = 0;
int HSVFilter::defaultLowS = 0;
int HSVFilter::defaultHighS = 0;
int HSVFilter::defaultLowV = 0;
int HSVFilter::defaultHighV = 0;

//using namespace cv;
HSVFilter::HSVFilter() {
    setID("hsv");
    setValues(defaultLowH, defaultHighH, defaultLowS, defaultHighS, defaultLowV, defaultHighV);
}

HSVFilter::HSVFilter(int lowH, int highH, int lowS, int highS, int lowV, int highV) {
    setValues(lowH, highH, lowS, highS, lowV, highV);
    setID("hsv");
}

bool HSVFilter::filter(Data *data) {
    // check for whether the input is of the correct type.      From Albert
    ImgData* imgData = dynamic_cast<ImgData*>(data);
    if (imgData == 0) {
        // track the error and return error
        track(data, filterID, 1, 1);
        return false;
    }

    //begin filtering squence
    cv::Mat mat = imgData->getImg();
    cv::Mat imgThresh = filter(mat);

    //setting the image to replace the old oe
    imgData->setImg(imgThresh);

    //track and return
    track(imgData, filterID, 0, 0);
    return true;
}

cv::Mat HSVFilter::filter(cv::Mat mat) {
    cv::Mat imgHSV;
    cv::Mat imgThresh = cv::Mat(mat.clone());

    cv::imshow("SARWDASDASd", mat);

    //cv::cvtColor(mat, imgHSV, cv::COLOR_RGB2BGR); //Convert the captured frame from BGR to HSV
    cv::cvtColor(mat,imgHSV,cv::COLOR_RGB2HSV);
    cv::inRange(imgHSV, cv::Scalar(lowH, lowS, lowV),
                cv::Scalar(highH, highS, highV), imgThresh); //Threshold the image

    //morphological opening (remove small objects from the foreground)
    cv::erode(imgThresh, imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::dilate(imgThresh, imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    //morphological closing (fill small holes in the foreground)
    cv::dilate(imgThresh, imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::erode(imgThresh, imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    cv::imshow("FUCK", imgThresh);

    return imgThresh;
}

void HSVFilter::setValues(int lowH, int highH, int lowS, int highS, int lowV, int highV) {
    this->lowH = lowH;
    this->highH = highH;
    this->lowS = lowS;
    this->highS = highS;
    this->lowV = lowV;
    this->highV = highV;
}

void HSVFilter::setH(int low, int high) {
    this->lowH = low;
    this->highH = high;
}

void HSVFilter::setS(int low, int high) {
    this->lowS = low;
    this->highS = high;
}

void HSVFilter::setV(int low, int high) {
    this->lowV = low;
    this->highV = high;
}
