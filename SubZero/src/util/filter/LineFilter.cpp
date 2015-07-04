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
    int linesFound = 0;
    cv::Mat src = imgData->getImg();
    cv::Mat dst;
    cv::Mat cdst = src.clone();
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);

    std::vector<cv::Vec2f> lines;
    //detects lines
    HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );
    //ending filter sequence

    //calculating the line equation
    linesEq.clear();
    float x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    for( size_t i = 0; i < lines.size(); i++ ){
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));

        x1 = pt1.x;
        y1 = pt1.y;
        x2 = pt2.x;
        y2 = pt2.y;
        //equation of line
        std::vector<float> eq;
        /*
        //general equation of a line, Ax + By = C
        eq.push_back(y2-y1);    //A = delta y
        eq.push_back(x2-x1);    //B = delta x
        eq.push_back();         //C = b * delta x*/

        //y = mx+b
        float M = (y2-y1) / (x2-x1);
        float B = y2 - x2*M;
        eq.push_back(M);
        eq.push_back(B);
        if (M < 5)  //aprox horizontal line
            eq.push_back(y2);   //give it the y value
        if (M > 9999) //vertical line
            eq.push_back(x2);   //x value

        linesEq.push_back(eq);
        linesFound++;

        //line(*cdst, pt1, pt2, cv::Scalar(0,0,255), 3, CV_AA);     //drawing the line
    }

    //should i set imgData to something?? -Carl

    //track and return
    this->track(imgData, this->filterID, 0,0);
    return linesFound == 0;
}

float yDiff = 40, xDiff = 40, diff = 40;
float maxSlope = 35;
float maxDiff = 30;
cv::Mat LineFilter::filter(cv::Mat src, int mode){
    cv::Mat dst;
    //cv::Mat cdst = cv::Mat(src.clone());
    cv::Mat cdst = src.clone();
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);

    if (mode == 0){
        std::vector<cv::Vec2f> lines;
        //detects lines
        HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

        linesEq.clear();
        float x1 = 0, x2 = 0, y1 = 0, y2 = 0;

        //draws the lines detected
        printf("-----------\n");
        for( size_t i = 0; i < lines.size(); i++ ){
            float rho = lines[i][0], theta = lines[i][1];
            cv::Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound(x0 + 1000*(-b));
            pt1.y = cvRound(y0 + 1000*(a));
            pt2.x = cvRound(x0 - 1000*(-b));
            pt2.y = cvRound(y0 - 1000*(a));

            x1 = pt1.x;
            y1 = pt1.y;
            x2 = pt2.x;
            y2 = pt2.y;
            //equation of line
            std::vector<float> eq;

            /*
            //general equation of a line, Ax + By = C
            float A = 0, B = 0, C = 0;
            if (std::abs(x2-x1) < xDiff){  //vertical line
                A = x2;
                printf("Vert ");
            }else if (std::abs(y2-y1) < yDiff){  //horzontal line
                B = y2;
                printf("Horz ");
            }else{
                float m = (y2-y1) / (x2-x1);
                b = y2- m*x2;
                a = -b/m;

                A = b;
                B = a;
                C = a*b;
            }
            bool repeat = false;
            //checks if existing line already exists
            for (std::vector<float> eqs: linesEq){
                if (std::abs(eqs[0]-A) < diff &&
                        std::abs(eqs[1]-B) < diff &&
                        std::abs(eqs[2]-C) < diff){
                    //very similar lines
                    repeat = true;
                }
            }

            if (!repeat){
                std::cout<< A  <<" "<< B <<" "<< C << std::endl;
                eq.push_back(A);    //A = delta y
                eq.push_back(B);    //B = delta x
                eq.push_back(C);    //C = b * delta x

                linesEq.push_back(eq);
                line(cdst, pt1, pt2, cv::Scalar(0,0,255), 3, CV_AA);       //drawing the line
            }*/


            //y = mx+b
            //B MIGHT BE USELSES, NEED FURTHER TESTING
            bool safeMath = true;
            float M = 0, B = 0;
            if (x2-x1 < 5){     //straight line
                safeMath = false;
                M = INFINITY;
                B = INFINITY;
            }
            if (safeMath){      //avoid div by 0 error
                M = (y2-y1) / (x2-x1);
                B = y2 - M*x2;
            }

            bool repeat = false;
            //check if there is a similar line already
            for (std::vector<float> lines: linesEq){
                //vert line situations
                if (M == INFINITY && lines[0] == INFINITY){
                    //check their x values
                    if (std::abs(lines[2] - ((x1+x2)/2)) < maxDiff){
                        repeat = true;
                        break;
                    }
                }
                //check if m is almost vertical
                else if (std::abs(M) > maxSlope && lines[0] == INFINITY){
                    std::cout<<"almost vert ";
                    std::cout<<std::abs(lines[2] - ((x1+x2)/2))<<std::endl;
                    if (std::abs(lines[2] - ((x1+x2)/2) ) < maxDiff){
                        repeat = true;
                        break;
                    }
                }
                else if (M == INFINITY && std::abs(lines[0])> maxSlope){
                    std::cout<<"almost vert II ";
                    std::cout<<std::abs(lines[2] - ((x1+x2)/2))<<std::endl;
                    if (std::abs(lines[2] - ((x1+x2)/2) ) < maxDiff){
                        repeat = true;
                        break;
                    }
                }
                //check if m and b are too similar or not
                else if (std::abs(lines[0] - M) < maxDiff &&
                         std::abs(lines[1]-B) < maxDiff){
                    repeat = true;
                    break;
                }
            }

            if (!repeat){
                eq.push_back(M);
                eq.push_back(B);
                std::cout<<M<<" "<<B<<" " << ((x1+x2)/2) << " ";
                if (std::abs(M) < 5){  //aprox horizontal line
                    eq.push_back(y2);   //give it the y value
                    std::cout<<y2;
                    printf(" horz line");
                }
                if (std::abs(M) > maxSlope){ //vertical line
                    eq.push_back(x2);   //x value
                    std::cout<<x2;
                    printf(" vertal line");
                }
                std::cout<<std::endl;

                linesEq.push_back(eq);
                line(cdst, pt1, pt2, cv::Scalar(0,0,255), 3, CV_AA);       //drawing the line
            }
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
