#include "VideoTesting.h"

/*VideoTesting::VideoTesting(){
    cv::VideoCapture cap("test.avi");
    if( !cap.isOpened()){
         std::cout << "Cannot open the video file" << std::endl;
         return;
    }
    double count = cap.get(CV_CAP_PROP_FRAME_COUNT); //get the frame count
    cap.set(CV_CAP_PROP_POS_FRAMES,count-1); //Set index to last frame
    this->cap = cap;
}*/
VideoTesting::VideoTesting(const std::string fileName){
    cv::VideoCapture cap(fileName);
    if( !cap.isOpened()){
         std::cout << "Cannot open the video file" << std::endl;
         return;
    }
    double count = cap.get(CV_CAP_PROP_FRAME_COUNT); //get the frame count
    cap.set(CV_CAP_PROP_POS_FRAMES,count-1); //Set index to last frame
    this->cap = cap;
}

std::vector<std::vector<cv::Point> > *contours;
std::vector<cv::Vec4i> hierarchy;

cv::Mat* getContours(cv::Mat* img){
    if (img->cols == 0) return 0;
    cv::Mat canny;
    contours = new std::vector<std::vector<cv::Point> >;
    //std::vector<cv::Vec4i> hierarchy;

    //std::cout<<"first"<<std::endl;

    cv::Canny(*img, canny, 50, 200, 3);
    //cv::cvtColor(gray, canny, CV_GRAY2BGR);

    cv::findContours(canny, *contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    cv::Mat drawing = cv::Mat::zeros(canny.size(), CV_8UC3);
    for (unsigned int i = 0; i < contours->size(); i++){
        cv::Scalar color = cv::Scalar(0, 255, 0);
        cv::drawContours(drawing, *contours, i, color, 2, 8, hierarchy, 0, cv::Point());
    }

    return new cv::Mat(drawing);
}
int compareRect(){     //copying last year's code; math complicated
    //if (img == NULL) return false;
    int boxesFound = 0;
    int minPoints = 6;
    double minArea = 50;
    double maxArea = 500;
    float lwMin = 2;
    float lwMax = 5;
    double areaMin = 0.6;
    double perimMin = 0.75;
    double perimMax = 1.2;
    for (std::vector<cv::Point> co: *contours){
        //error checking
        if (co.size() < minPoints){
            std::cout << "Not enough Points" << std::endl;
            continue;
        }
        double area = cv::contourArea(co);
        if (area < minArea){
            std::cout << area << " Not enough Area" << std::endl;
            continue;
        }
        if (area > maxArea){
            std::cout << area << " Too much Area" << std::endl;
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
            std::cout << "LW ratio too small" << std::endl;
            continue;
        }
        if (lw_ratio > lwMax){
            std::cout << "LW ratio too big" << std::endl;
            continue;
        }
        double perimneter = cv::arcLength(co, 1);
        double perim_ratio = perimneter/ (2*length+2*width);
        double area_ratio = area/(length*width);
        if (area_ratio < areaMin){
            std::cout << "area ratio too small" << std::endl;
            continue;
        }
        if (perim_ratio > perimMax){
            std::cout << "area ratio too small" << std::endl;
            continue;
        }
        if (perim_ratio < perimMin){
            std::cout << "area ratio too small" << std::endl;
            continue;
        }
/*
        MvRotatedBox rbox;
        rbox.center.x = rect.center.x;
        rbox.center.y = rect.center.y;
        rbox.length = length;
        rbox.width = width;
        rbox.angle = angle;
        rbox.m1 = 100;
        rbox.m2 = 255;
        rbox.m3 = 0;
        */
        std::cout<<"FOUND"<<std::endl;
        boxesFound++;
    }

    return boxesFound;
}

int thresh = 150;
int max_thresh = 200;

cv::Mat* boundingBoxes(cv::Mat* src){
    cv::Mat threshold_output;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    /// Detect edges using Threshold
    //cv::threshold(*src, threshold_output, thresh, 255, cv::THRESH_BINARY );
    cv::Canny(*src, threshold_output, 50, 200, 3);
    /// Find contours
    cv::findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    /// Find the rotated rectangles and ellipses for each contour
    std::vector<cv::RotatedRect> minRect( contours.size() );
    std::vector<cv::RotatedRect> minEllipse( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
       { minRect[i] = minAreaRect( cv::Mat(contours[i]) );
         if( contours[i].size() > 5 )
           { minEllipse[i] = fitEllipse( cv::Mat(contours[i]) ); }
       }

    /// Draw contours + rotated rects + ellipses
    cv::Mat drawing = cv::Mat::zeros( threshold_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
       {
         cv::Scalar color = cv::Scalar(0, 255, 0);
         // contour
         cv::drawContours(drawing, contours, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point() );
         // ellipse
         ellipse( drawing, minEllipse[i], color, 2, 8 );
         // rotated rectangle
         cv::Point2f rect_points[4]; minRect[i].points( rect_points );
         for( int j = 0; j < 4; j++ )
            line( drawing, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
       }
    return new cv::Mat(drawing);
}

void VideoTesting::run(){
    for (int i = 0; i < 2*33; i++) getNextFrame();
    cv::namedWindow("Orginal",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("HSV Filtered",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Line Filtered",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Canny", CV_WINDOW_AUTOSIZE);
    cv::moveWindow("Orginal", 1400, 100);
    cv::moveWindow("HSV Filtered", 1400, 500);
    cv::moveWindow("Line Filtered", 800, 100);
    cv::moveWindow("Canny", 800, 500);
    cv::Mat frame;
    cv::Mat* filtered;
    cv::Mat* lineFiltered;
    cv::Mat* contour;


    HSVFilter hf(25, 179, 0, 255, 0,255);
    LineFilter lf(0);
    while (1){
        frame = this->getNextFrame();
        if(frame.cols == 0)break;       //exit when there is no next fraame

        filtered = hf.filter(&frame);
        lineFiltered = lf.filter(filtered);
        //contour = getContours(filtered);
        contour = getContours(filtered);
        //contour = boundingBoxes(lineFiltered);

        imshow("Orginal", frame);
        imshow("HSV Filtered", *filtered);
        imshow("Line Filtered", *lineFiltered);
        imshow("Canny", *contour);

        compareRect();


        int key = cv::waitKey((33));        //wait for 33ms, ~= 30fps;
        //std::cout<<key<<std::endl;
        if (key == 27) break;               //if user press esc, break the loop
        else if(key == 98) cv::waitKey(0);  //"b" key, "pasues" play
    }
    std::cout << "End of video feed" << std::endl;
}

cv::Mat VideoTesting::getNextFrame(){
    cv::Mat frame;
    bool success = cap.read(frame);
    if (!success){
      std::cout << "Cannot read  frame " << std::endl;
      //return 0;
    }
    return frame;
}
