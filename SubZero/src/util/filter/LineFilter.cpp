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

LineFilter::~LineFilter(){
    delete logger;
}

void LineFilter::println(std::string s){
    if (debug){
        //std::cout<<s<<std::endl;
        logger->info(s);
    }
}

void LineFilter::println(float f){
    if (debug)
        //std::cout<<f<<std::endl;
        logger->info(std::to_string(f));
}

void LineFilter::print(std::string s){
    if (debug)
        //std::cout<<s;
        logger->info(s);
}

void LineFilter::print(float f){
    if (debug)
        //std::cout<<f;
        logger->info(std::to_string(f));
}

float yDiff = 40, xDiff = 40, diff = 40;
float maxSlope = 25;
float maxDiff = 30;

bool LineFilter::filter(Data *data){
    // check for whether the input is of the correct type.          From Albert
    ImgData* imgData = dynamic_cast<ImgData*>(data);
    if (imgData == 0) {
        // track the error and return error
        this->track(data,this->filterID,1,1);
        return false;
    }
    cv::imshow("asdf", filter(imgData->getImg().clone(),0));

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
            //M = (y2-y1) / (x2-x1);
            double realtheta = (rho < 0)? theta - M_PI:theta;
            realtheta = -realtheta +  M_PI/2;
            M = tan(realtheta);
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
                //std::cout<<"almost vert ";
                //std::cout<<std::abs(lines[2] - ((x1+x2)/2))<<std::endl;
                if (std::abs(lines[2] - ((x1+x2)/2) ) < maxDiff){
                    repeat = true;
                    break;
                }
            }
            else if (M == INFINITY && std::abs(lines[0])> maxSlope){
                //std::cout<<"almost vert II ";
                //std::cout<<std::abs(lines[2] - ((x1+x2)/2))<<std::endl;
                if (std::abs(lines[2] - ((x1+x2)/2) ) < maxDiff){
                    repeat = true;
                    break;
                }
            }
            //check if m is too similar or not, b is too different to check
            else if (std::abs(lines[0] - M) < maxDiff){
                if (M > 15){ //vertical lines
                    //check if the intersection point is near the average x
                    if (std::abs((B-lines[1])/(lines[0]-M))-(x1+x2)/2 < maxDiff){
                        repeat = true;
                        break;
                    }
                }else{      //horziontal lines
                    if (std::abs((B-lines[1])/(lines[0]-M))*M - (y1+y2)/2 < maxDiff){
                        repeat = true;
                        break;
                    }
                }
            }
        }

        if (!repeat){
            eq.push_back(M);
            eq.push_back(B);
            //std::cout<<M<<" "<<B<<" " << ((x1+x2)/2) << " ";
            if (std::abs(M) < 5){  //aprox horizontal line
                eq.push_back(y2);   //give it the y value
                //std::cout<<y2;
                //printf(" horz line");
            }
            if (std::abs(M) > maxSlope){ //vertical line
                eq.push_back(x2);   //x value
                //std::cout<<x2;
                //printf(" vertal line");
            }
            //std::cout<<std::endl;

            linesEq.push_back(eq);
            linesFound++;
            //line(*cdst, pt1, pt2, cv::Scalar(0,0,255), 3, CV_AA);     //drawing the line
        }
    }

    //should i set imgData to something?? -Carl

    //track and return
    this->track(imgData, this->filterID, 0,0);
    //println(linesFound != 0);
    return linesFound != 0;
}

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
        //println("-----------\n");
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

            //y = mx+b
            //B MIGHT BE USELESS, NEED FURTHER TESTING
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
                    //std::cout<<"almost vert ";
                    //std::cout<<std::abs(lines[2] - ((x1+x2)/2))<<std::endl;
                    if (std::abs(lines[2] - ((x1+x2)/2) ) < maxDiff){
                        repeat = true;
                        break;
                    }
                }
                else if (M == INFINITY && std::abs(lines[0])> maxSlope){
                    //std::cout<<"almost vert II ";
                    //std::cout<<std::abs(lines[2] - ((x1+x2)/2))<<std::endl;
                    if (std::abs(lines[2] - ((x1+x2)/2) ) < maxDiff){
                        repeat = true;
                        break;
                    }
                }
                //check if m is too similar or not, b is too different to check
                else if (std::abs(lines[0] - M) < maxDiff){
                    if (M > 15){ //vertical lines
                        //check if the intersection point is near the average x
                        if (std::abs((B-lines[1])/(lines[0]-M))-(x1+x2)/2 < maxDiff){
                            repeat = true;
                            break;
                        }
                    }else{      //horziontal lines
                        //print("horz ");
                        //println((y1+y2)/2);
                        float x = (B-lines[1])/(lines[0]-M);
                        float y = x * M + B;
                        if (x < cdst.size().width && y < cdst.size().height){
                            repeat = true;
                            break;
                        }
                    }
                }
            }

            if (!repeat){
                eq.push_back(M);
                eq.push_back(B);
                //print(M);
                //print(" ");
                //print(B);
                //print(" ");
                //print((x1+x2)/2);
                if (std::abs(M) < 0.5){  //aprox horizontal line
                    eq.push_back(y2);   //give it the y value
                    print(y2);
                    print(" horz line");
                }
                if (std::abs(M) > maxSlope){ //vertical line
                    eq.push_back(x2);   //x value
                    print(x2);
                    print(" vertal line");
                }
                //println("");

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
