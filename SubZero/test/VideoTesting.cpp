#include "VideoTesting.h"

VideoTesting::VideoTesting(const std::string fileName){
/*    cv::VideoCapture cap(fileName);
    if( !cap.isOpened()){
         std::cout << "Cannot open the video file" << std::endl;
         return;
    }
    double count = cap.get(CV_CAP_PROP_FRAME_COUNT); //get the frame count
    cap.set(CV_CAP_PROP_POS_FRAMES,count-1); //Set index to last frame
    this->cap = cap;*/
}
CvCapture* capture;  //Capture using any camera connected to your system
VideoTesting::VideoTesting(int deviceID) {
    //cap.open(deviceID);
    capture = cvCaptureFromCAM(deviceID);
}

//================get next frame from camera=====================================


cv::Mat getNextCameraFrame(){
    IplImage* frame = cvQueryFrame(capture); //Create image frames from capture
    cv::Mat temp = cv::cvarrToMat(frame,true,true,0);
    //delete frame;
    return temp;
}
/*
cv::Mat VideoTesting::getNextCameraFrame(){
    cv::Mat frame;
    cap.read(frame);
    return frame;
}*/
//================HSV filter==========================================
cv::Mat HSVFilter(cv::Mat mat, int lowH, int highH, int lowS, int highS, int lowV, int highV){
    //cv::Mat* mat = data->getImg();
    cv::Mat imgHSV;
    //cv::Mat imgThresh = cv::Mat(mat.clone());
    cv::Mat imgThresh = mat.clone();

    cv::cvtColor(mat, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

    cv::inRange(imgHSV, cv::Scalar(lowH, lowS, lowV),
            cv::Scalar(highH, highS, highV), imgThresh); //Threshold the image

    //morphological opening (remove small objects from the foreground)
    cv::erode(imgThresh, imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::dilate(imgThresh, imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    //morphological closing (fill small holes in the foreground)
    cv::dilate(imgThresh, imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::erode(imgThresh, imgThresh, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    return imgThresh;
}
//================================= rgb filter =================================
cv::Mat RGBFilter(cv::Mat img, int r, int g, int b){

    assert(img.type() == CV_8UC3);

    cv::Mat pic;
    inRange(img, cv::Scalar(0, 0, 0), cv::Scalar(g, b, r), pic);

    return pic;
}

//=============================
cv::Mat HCT(cv::Mat img){
    cv::Mat src = cv::Mat::zeros(img.size(), CV_8UC3);
    cv::Mat src_gray = img.clone();

    /// Convert it to gray
    //cvtColor(img, src_gray, CV_BGR2GRAY );

    /// Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, cv::Size(9, 9), 2, 2 );

    std::vector<cv::Vec3f> circles;

    /// Apply the Hough Transform to find the circles
    HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );

    /// Draw the circles detected
    for( size_t i = 0; i < circles.size(); i++ )
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle( src, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( src, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
    }

    return src;
}
//============================== moments ================================
cv::Mat Moments(cv::Mat img){
    cv::Mat canny_output;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    int thresh = 100;
    /// Detect edges using canny
    Canny(img, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    /// Get the moments
    std::vector<cv::Moments> mu(contours.size() );
    for( uint64_t i = 0; i < contours.size(); i++ )
    { mu[i] = moments( contours[i], false ); }

    ///  Get the mass centers:
    std::vector<cv::Point2f> mc( contours.size() );
    for( uint64_t i = 0; i < contours.size(); i++ )
    { mc[i] = cv::Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }


    /// Draw contours
    cv::Mat drawing = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
    for( uint64_t i = 0; i< contours.size(); i++ )
    {
        cv::Scalar color = cv::Scalar(0, 255, 0);
        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
        circle( drawing, mc[i], 4, color, -1, 8, 0 );
    }


    /// Calculate the area with the moments 00 and compare with the result of the OpenCV function
    //printf("\t Info: Area and Contour Length \n");
    for( uint64_t i = 0; i< contours.size(); i++ )
    {
        //printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength( contours[i], true ) );
        cv::Scalar color = cv::Scalar(255, 0, 0);
        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
        circle( drawing, mc[i], 4, color, -1, 8, 0 );
    }
    return drawing;
}
//============blur filter============================================
cv::Mat blur(cv::Mat src, int max){
    //cv::Mat* dst = new cv::Mat(src->clone());
    cv::Mat dst(cv::Mat::zeros(src.size(), CV_8UC3));
    max = max*2+1;

    GaussianBlur(src, dst, cv::Size(max, max), 0,0);
    //blur(*src, *dst, cv::Size(3,3), cv::Point(-1,-1));
    //medianBlur(*src, *dst, max);
    //bilateralFilter(*src, *dst, max, max*2, max/2);
    return dst;
}

//==============================================================
void VideoTesting::run(){
    //for (int i = 0; i < 2*33; i++) getNextFrame();
    cv::namedWindow("Orginal",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("HSV Filtered",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Line Filtered",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Canny", CV_WINDOW_AUTOSIZE);
    int Type = 0;
    if (Type == 2){
    cv::moveWindow("Orginal", 1400, 50);           //reading from photo
    cv::moveWindow("HSV Filtered", 1000, 50);
    cv::moveWindow("Line Filtered", 600, 50);
    cv::moveWindow("Canny", 100, 50);}
    else if (Type == 1){
    cv::moveWindow("Orginal", 1200, 50);           //reading from camera
    cv::moveWindow("HSV Filtered", 1200, 500);
    cv::moveWindow("Line Filtered", 600, 50);
    cv::moveWindow("Canny", 600, 500);}
    else if (Type == 0){
    cv::moveWindow("Orginal", 1400, 100);         //reading from video
    cv::moveWindow("HSV Filtered", 1400, 500);
    cv::moveWindow("Line Filtered", 800, 100);
    cv::moveWindow("Canny", 800, 500);}

    cv::Mat frame;
    cv::Mat filtered;
    cv::Mat filtered2;
    cv::Mat lineFiltered;
    cv::Mat contour;

    cv::namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    int iLowH = 30;
    int iHighH = 152;
    int iLowS = 75;
    int iHighS = 255;
    int iLowV = 100;
    int iHighV = 255;
    int max = 1;
    //Create trackbars in "Control" window
    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);
    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);
    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);
    cvCreateTrackbar("max", "Control", &max, 130);

    //HSVFilter hf(25, 179, 0, 255, 0,255);
    LineFilter lf;
    ShapeFilter sf(1, 5);
    BlurFilter bf(2, 0.2f);
    BlurFilter bf2(1, 0.4f);
    if (Type == 0)
        frame = cv::imread("buoy2.png");       //img
    cv::Scalar color = cv::Scalar(255, 0, 0);

    while (1){
        //contour = cv::Mat::zeros(frame.size(), CV_8UC3);
        if (Type == 2)
            frame = this->getNextFrame(); //video
        if (Type == 1)
            frame = getNextCameraFrame(); //webcam
        contour = frame.clone();
        if(frame.cols == 0)break;       //exit when there is no next fraame

        //filtered = hf.filter(&frame);
        filtered2 = HSVFilter(frame, iLowH, iHighH, iLowS, iHighS, iLowV, iHighV);
        filtered = HSVFilter(frame, iLowH, iHighH, iLowS, iHighS, iLowV, iHighV);
        //filtered = blur(filtered,max);
        //filtered = bf.filter(filtered2);
        //filtered = bf2.filter(filtered);
        lineFiltered = lf.filter(filtered, 0);
        //lineFiltered = Moments(filtered);

        //draw rectangle
        if (sf.findRect(filtered)){
            std::vector<cv::RotatedRect> rect = sf.getRect();
            for (cv::RotatedRect rekt: rect){
                cv::Point2f rect_points[4]; rekt.points( rect_points );
                for( int j = 0; j < 4; j++ )
                   line( contour, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
                //delete rect;
            }
        }

        //draw circle
        if (sf.findCirc(filtered)){
            auto rad = sf.getRad();
            auto cent = sf.getCenter();
            //radius
            for (unsigned int i = 0; i < rad.size(); i++){
                cv::circle(lineFiltered, cent[i], rad[i], cv::Scalar(255,0,0) );
            }
            //center
            for (unsigned int i = 0; i < rad.size(); i++){
                cv::circle(lineFiltered, cent[i], 2, cv::Scalar(0,255,0));
            }
        }

        //gets the mass center; testing purposes only
        auto t = sf.findMassCenter(filtered);
        for (cv::Point2f p: t){
            cv::circle(lineFiltered, p, 2, cv::Scalar(0,0,255));
        }

        imshow("Orginal", frame);
        imshow("HSV Filtered", filtered);
        imshow("Line Filtered", lineFiltered);
        imshow("Canny", contour);
        int key = cv::waitKey((33));        //wait for 33ms, ~= 30fps;
        //std::cout<<key<<std::endl;
        if (key == 27) break;               //if user press esc, break the loop
        else if(key == 98) cv::waitKey(0);  //"b" key, "pasues" play

        /*delete filtered;
        delete filtered2;
        delete lineFiltered;*/
    }
    cvReleaseCapture(&capture);
    //cap.release();
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
