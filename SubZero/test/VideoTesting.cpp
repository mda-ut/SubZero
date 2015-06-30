#include "VideoTesting.h"

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
//================get next frame from camera=====================================
CvCapture* capture = cvCaptureFromCAM(0);  //Capture using any camera connected to your system
cv::Mat getNextCameraFrame(){
    IplImage* frame = cvQueryFrame(capture); //Create image frames from capture
    return cv::cvarrToMat(frame,true,true,0); // If you hit spacebar an image will be saved
}
//================HSV filter==========================================
cv::Mat HSVFilter(cv::Mat mat, int lowH, int highH, int lowS, int highS, int lowV, int highV){
    //cv::Mat* mat = data->getImg();
    cv::Mat imgHSV;
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

void VideoTesting::run(){
    for (int i = 0; i < 2*33; i++) getNextFrame();
    cv::namedWindow("Orginal",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("HSV Filtered",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Line Filtered",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Canny", CV_WINDOW_AUTOSIZE);
    /*cv::moveWindow("Orginal", 1400, 50);           //reading from photo
    cv::moveWindow("HSV Filtered", 1000, 50);
    cv::moveWindow("Line Filtered", 600, 50);
    cv::moveWindow("Canny", 100, 50);*/
    cv::moveWindow("Orginal", 1200, 50);           //reading from camera
    cv::moveWindow("HSV Filtered", 1200, 500);
    cv::moveWindow("Line Filtered", 600, 50);
    cv::moveWindow("Canny", 600, 500);
    /*cv::moveWindow("Orginal", 1400, 100);         //reading from video
    cv::moveWindow("HSV Filtered", 1400, 500);
    cv::moveWindow("Line Filtered", 800, 100);
    cv::moveWindow("Canny", 800, 500);*/
    cv::Mat frame;
    cv::Mat filtered;
    cv::Mat lineFiltered;
    cv::Mat contour;

    cv::namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    int iLowH = 30;
    int iHighH = 179;
    int iLowS = 0;
    int iHighS = 255;
    int iLowV = 0;
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
    ShapeFilter sf(1);
    BlurFilter bf(2, 0.4f);
    //frame = cv::imread("rect.jpg");       //img
    cv::Scalar color = cv::Scalar(255, 0, 0);

    while (1){
        //contour = cv::Mat::zeros(frame.size(), CV_8UC3);
        //frame = this->getNextFrame(); //video
        frame = getNextCameraFrame(); //webcam
        contour = frame.clone();
        if(frame.cols == 0)break;       //exit when there is no next fraame

        //filtered = hf.filter(&frame);
        filtered = HSVFilter(frame, iLowH, iHighH, iLowS, iHighS, iLowV, iHighV);
        //filtered = blur(filtered,max);
        filtered = bf.filter(filtered);
        lineFiltered = lf.filter(filtered, 0);
        sf.findRect(filtered);

        //contour = getContours(filtered);
        //getContours(filtered);//Canny(*filtered, *contour, 50, 200, 3);
        //contour = boundingBoxes(filtered);


        //compareRect();
        cv::RotatedRect rect = sf.getRect();
        if (rect.size.area() != 0){
        cv::Point2f rect_points[4]; sf.getRect().points( rect_points );
        for( int j = 0; j < 4; j++ )
           line( contour, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );}

        imshow("Orginal", frame);
        imshow("HSV Filtered", filtered);
        imshow("Line Filtered", lineFiltered);
        imshow("Canny", contour);
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
