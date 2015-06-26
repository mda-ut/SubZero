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

void VideoTesting::run(){
    cv::namedWindow("Orginal",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("HSV Filtered",CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Line Filtered",CV_WINDOW_AUTOSIZE);
    cv::Mat frame;
    cv::Mat* filtered;
    cv::Mat lineFiltered;
    HSVFilter hf(25, 179, 0, 255, 0,255);
    LineFilter lf(0);
    while (1){
        frame = this->getNextFrame();
        if(frame.cols == 0)break;       //exit when there is no next fraame

        filtered = hf.filter(&frame);
        lineFiltered = lf.filter(filtered);
        imshow("Orginal", frame);
        imshow("HSV Filtered", *filtered);
        imshow("Line Filtered", lineFiltered);
        if (cv::waitKey(33) == 27) break;       //wait for 33ms, ~= 30fps; if user press esc, break the loop
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
