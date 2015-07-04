#include "ShapeFilter.h"


ShapeFilter::ShapeFilter(int shape, int amount)
{
    setShape(shape);
    this->max = amount;
    //contours = new std::vector<std::vector<cv::Point> >;
}

void ShapeFilter::print(int i){
    if (debug)
        //std::cout<<i;
        logger->info(std::to_string(i));
}

void ShapeFilter::println(std::string s){
    if (debug)
        //std::cout<< s << std::endl;
        logger->info(s);
}

int ShapeFilter::filter(Data *data){
    // check for whether the input is of the correct type.          From Albert
    ImgData* imgData = dynamic_cast<ImgData*>(data);
    if (imgData == 0) {
        // track the error and return error
        this->track(data,this->filterID,1,1);
        return 1;
    }

   //beging filtering process
    if (shape == 1){    //rectangle
        return this->findRect((imgData->getImg()));   //lazy to copy+paste everything
    }
    //ending filtering process

    //track and return
    this->track(imgData, this->filterID, 0,0);
    return 0;
}

double MEAN2(double a, double b){
    return ((fabs((a) + (b)))/2.0);
}

std::vector<float> ShapeFilter::getRad(){
    return this->radius;
}

std::vector<cv::Point2f> ShapeFilter::getCenter(){
    return this->center;
}

bool ShapeFilter::findCirc(cv::Mat img){
    //getting the contours
    cv::Mat canny;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    float radius;
    cv::Point2f center;
    this->radius.clear();
    this->center.clear();

    int thresh = 100;
    // Detect edges using canny
    Canny(img, canny, thresh, thresh*2, 3 );
    // Find contours
    findContours( canny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    int circlesFound = 0;
    //constants
    unsigned int minPoints = 6;
    double minArea = 500;
    float minRad = 400;

    for (std::vector<cv::Point> co: contours){
        if (co.size() < minPoints){
            println("Circle Not enough Points");
            continue;
        }

        double area = cv::contourArea(co);
        if (area < minArea) {
            println ("Circle not enough area area");
            continue;
        }

        /*
        /// Get the moments
        std::vector<cv::Moments> mu(co.size() );
        for( int i = 0; i < co.size(); i++ ){
            mu[i] = moments( co[i], false );
        }

        ///  Get the mass centers:
        std::vector<cv::Point2f> mc( contours.size() );
        for( int i = 0; i < contours.size(); i++ )
        { mc[i] = cv::Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }
*/

        cv::Moments cvmoments = moments(co, false);
        double nu11 = cvmoments.nu11;
        double nu20 = cvmoments.nu02;
        double nu02 = cvmoments.nu20;
        double nu21 = cvmoments.nu21;
        double nu12 = cvmoments.nu12;
        double nu03 = cvmoments.nu03;
        double nu30 = cvmoments.nu30;

        double r03 = fabs(nu30 / nu03);
        r03 = (r03 > 1) ? r03 : 1.0/r03;
        double r12 = fabs(nu12 / nu21);
        r12 = (r12 > 1) ? r12 : 1.0/r12;
        double r02 = fabs(nu02 / nu20);
        r02 = (r02 > 1) ? r02 : 1.0/r02;

        double r11 = fabs( MEAN2(nu02,nu20) / nu11);
        double R = MEAN2(nu20,nu02) / std::max((MEAN2(nu21,nu12)), (MEAN2(nu30,nu03)));
        bool pass = true;
        pass = (r03 <= 25.0) && (r12 <= 12.0) && (r02 <= 12.0) && (r11 > 2.5) && (R > 25);

        if (!pass){
            println("Circle failed math test");
            continue;
        }

        // get min enclosing circle and radius
        //CvPoint2D32f centroid32f;

        //cv::minEnclosingCircle(co, &centroid32f, &radius);
        cv::minEnclosingCircle(co, center, radius);

        if (radius > minRad || radius < 0) {
            println("Circle radius too small");
            continue;
        }

        // do checks on area and perimeter
        double area_ratio = area / (CV_PI*radius*radius);
        //double perimeter_ratio = perimeter / (2*CV_PI*radius);
        if (area_ratio < 0.7) {
            println("Circle fail Area");
            continue;
        }

        bool repeat = false;
        //check if circle is found already
        for (unsigned int i = 0; i < this->center.size(); i++){
            cv::Point2f c = this->center[i];
            if (std::abs(c.x-center.x) < 20 && std::abs(c.y - center.y) < 20){
                repeat = true;
                break;
            }
        }

        if (!repeat){
            //check if i found the number of circles requested
            if (this->center.size() < max){
                println("Found circle");
                this->radius.push_back(radius);
                this->center.push_back(center);
                circlesFound++;
            }else{
                println("Already found enough circles");
            }
        }else{
            println("Already found this circle");
        }
    }
    return circlesFound != 0;
}

bool ShapeFilter::findRect(cv::Mat img){
    //getting the contours
    cv::Mat canny;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Canny(img, canny, 50, 20, 3);
    cv::findContours(canny, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    //searching for rectangles
    int boxesFound = 0;
    //constants
    unsigned int minPoints = 6;
    double minArea = 500;
    double maxArea = 500000;
    float lwMin = 1;
    float lwMax = 5;
    double areaMin = 0.6;
    double perimMin = 0.75;
    double perimMax = 1.2;
    rektangles.clear();

    for (std::vector<cv::Point> co: contours){
        //error checking
        if (co.size() < minPoints){
            println("Rect Not enough Points");
            continue;
        }
        double area = cv::contourArea(co);
        if (area < minArea){
            print(area);
            println(" Rect Not enough Area");
            continue;
        }
        if (area > maxArea){
            print(area);
            println(" Rect Too much Area");
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
            println("Rect LW ratio too small");
            continue;
        }
        if (lw_ratio > lwMax){
            println("Rect LW ratio too big");
            continue;
        }
        double perimeter = cv::arcLength(co, 1);
        double perim_ratio = perimeter/ (2*length+2*width);
        double area_ratio = area/(length*width);
        if (area_ratio < areaMin){
            println("Rect area ratio too small");
            continue;
        }
        if (perim_ratio > perimMax){
            println("Rect area ratio too small");
            continue;
        }
        if (perim_ratio < perimMin){
            println("Rect area ratio too small");
            continue;
        }

        if (rektangles.size() < max){
            cv::RotatedRect temp = cv::RotatedRect(rect);
            rektangles.push_back(temp);

            println("RECT FOUND");
            boxesFound++;
        }
    }
    return boxesFound != 0;
}

void ShapeFilter::setShape(int shape){
    this->shape = shape;
    if (shape == 0) this->setID("rect");
}

std::vector<cv::RotatedRect> ShapeFilter::getRect(){
    return rektangles;
}

std::vector<cv::Point2f> ShapeFilter::findMassCenter(cv::Mat img){
    //getting the contours
    cv::Mat canny;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Canny(img, canny, 50, 20, 3);
    cv::findContours(canny, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    double max = 0;
    double area = 0;
    int index = 0;

    std::vector<cv::Moments> mu(contours.size() );
    for( int i = 0; i < contours.size(); i++ )
    {
        mu[i] = cv::moments( contours[i], false );
        area = cv::contourArea(contours[i]);
        if (area > max){
            max = area;
            index = i;
        }
    }

    //  Get the mass centers:
    std::vector<cv::Point2f> mc( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
    {mc[i] = cv::Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );}

    std::vector<cv::Point2f> result;
    if (max > 0)
        result.push_back(mc[index]);
    return result;
}
