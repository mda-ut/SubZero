/**
  * LineFilter.cpp
  * Created on: June 19, 2015
  * Author: James534
  */

#include "LineFilter.h"

LineFilter::LineFilter()
{
    this->setID("line");
}

int LineFilter::filter(Data *data){
    // check for whether the input is of the correct type.          From Albert
    ImgData* imgData = dynamic_cast<ImgData*>(data);
    if (imgData == 0) {
        // track the error and return error
        this->track(data,this->filterID,1,1);
        return 1;
    }

    //begin filter sequence
    cv::Mat dst;
    cv::Mat *cdst = new cv::Mat(imgData->getImg()->clone());
    Canny(*imgData->getImg(), dst, 50, 200, 3);
    cvtColor(dst, *cdst, CV_GRAY2BGR);

    std::vector<cv::Vec2f> lines;
    //detects lines
    HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );
    //ending filter sequence

    //calculating the line equation
    linesEq.clear();
    for( size_t i = 0; i < lines.size(); i++ ){
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));

        //equation of line
        std::vector<float> eq;
        eq.push_back(((float)(pt2.y-pt1.y))/((float)(pt2.x-pt1.x)));
        eq.push_back((float)pt1.y - eq[0]*(float(pt1.x)));
        linesEq.push_back(eq);

        //line(*cdst, pt1, pt2, cv::Scalar(0,0,255), 3, CV_AA);     //drawing the line
    }

    //track and return
    this->track(imgData, this->filterID, 0,0);
    return 0;
}

cv::Mat LineFilter::filter(cv::Mat src, int mode){
    cv::Mat dst;
    cv::Mat cdst = cv::Mat(src.clone());
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);

    if (mode == 0){
        std::vector<cv::Vec2f> lines;
        //detects lines
        HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

        linesEq.clear();

        //draws the lines detected
        for( size_t i = 0; i < lines.size(); i++ ){
            float rho = lines[i][0], theta = lines[i][1];
            cv::Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound(x0 + 1000*(-b));
            pt1.y = cvRound(y0 + 1000*(a));
            pt2.x = cvRound(x0 - 1000*(-b));
            pt2.y = cvRound(y0 - 1000*(a));

            //equation of line
            std::vector<float> eq;
            eq.push_back(((float)(pt2.y-pt1.y))/((float)(pt2.x-pt1.x)));
            eq.push_back((float)pt1.y - eq[0]*(float(pt1.x)));
            linesEq.push_back(eq);

            line(cdst, pt1, pt2, cv::Scalar(0,0,255), 3, CV_AA);       //drawing the line
        }
    }
    else{
        std::vector<cv::Vec4i> lines;
        HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
        for( size_t i = 0; i < lines.size(); i++ ){
            cv::Vec4i l = lines[i];
            line(cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
                    cv::Scalar(0,0,255), 3, CV_AA);
        }
    }

    return cdst;
}

std::vector<std::vector<float> > LineFilter::getlineEq(){
    return linesEq;
}
