#include "BlurFilter.h"

BlurFilter::BlurFilter(int mode, float intensity){
    setMode(mode);
    setIntensity(intensity);
}

int roundToOdd(float);

int BlurFilter::filter(Data *data){
    // check for whether the input is of the correct type.
    ImgData* imgData = dynamic_cast<ImgData*>(data);
    if (imgData == 0) {
        // track the error and return error
        this->track(data,this->filterID,1,1);
        return 1;
    }

    cv::Mat src = imgData->getImg();
    cv::Mat dst = filter(src);
    imgData->setImg(dst);

    return 0;
}

cv::Mat BlurFilter::filter(cv::Mat src){
    cv::Mat dst = src.clone();
    //all parameter other than max is set to the default from the opencv blur tutorial
    if (mode == 0){
        int max = roundToOdd(BLURMAX*intensity);
        blur(src, dst, cv::Size(max,max), cv::Point(-1,-1));
    }else if (mode == 1){
        int max = roundToOdd(GAUSMAX*intensity);
        GaussianBlur(src, dst, cv::Size(max, max), 0,0);
    }else if (mode == 2){
        int max = roundToOdd(MEDIMAX*intensity);
        medianBlur(src, dst, max);
    }else if (mode == 3){
        int max = roundToOdd(BILAMAX*intensity);
        bilateralFilter(src, dst, max, max*2, max/2);
    }else {     //default blur is normal blur
        int max = roundToOdd(BLURMAX*intensity);
        blur(src, dst, cv::Size(max,max), cv::Point(-1,-1));
    }
    return dst;
}

void BlurFilter::setMode(int mode){
    this->mode = mode;
    if (mode == 0) this->setID("blur");
    else if (mode == 1) this->setID("gaussianBlur");
    else if (mode == 2) this->setID("medianBlur");
    else if (mode == 3) this->setID("bilateralBlur");
}

void BlurFilter::setIntensity(float inten){
    if (inten > 1.0) inten = 1.0;
    if (inten < 0.0) inten = 0.0;
    intensity = inten;
}

int roundToOdd(float i){
    int rounded = round(i);
    if (rounded%2 == 1) return rounded;
    else{
        if (i - (float)rounded < 0.0)
            return rounded-1;
        else
            return rounded+1;
    }
}
