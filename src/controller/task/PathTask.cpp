#include "PathTask.h"
#include "Timer.h"

#include <math.h>

PathTask::PathTask() {
    moving = false;
    alignThreshold = 75;
}

PathTask::PathTask(Model* cameraModel, TurnTask *turnTask, SpeedTask *speedTask) {
    this->cameraModel = dynamic_cast<CameraModel*>(cameraModel);
    this->turnTask = turnTask;
    this->speedTask = speedTask;

    moving = false;
    alignThreshold = 75;
}

PathTask::~PathTask() {
    delete logger;
}

void PathTask::setSpeed(float amount) {
    speedTask->setTargetSpeed(amount);
    speedTask->execute();
    if (amount != 0) {
        moving = true;
    } else {
        moving = false;
    }
    logger->info("Speed set to " + std::to_string(amount));
}

void PathTask::stop() {
    // Stop
    setSpeed(0);
}

void PathTask::rotate(float angle) {
    logger->debug("Rotating sub by " + std::to_string(angle) + " degrees");
    turnTask->setYawDelta(angle);
    turnTask->execute();
    usleep(5000000);
}

void PathTask::moveTo(cv::Point2f pos) {
    //TODO: Log this with useful debugs
    // Pretty much in line
    if (std::abs(pos.x - imgWidth / 2) < alignThreshold) {
        //float distance = std::sqrt(pos.x * pos.x + pos.y * pos.y);
        if (pos.y - imgHeight / 2 > 0) {
            logger->info("Moveto moving forwards");
            setSpeed(forwardSpeed);
        } else {
            logger->info("Moveto moving backwards");
            setSpeed(-forwardSpeed);
        }
    } else {
        //float ang = atan2(pos.y - imgHeight / 2, pos.x - imgWidth / 2) * 180 / M_PI;
        float ang = 5;
        ang *= std::abs(pos.x-imgWidth/2)/(pos.x-imgWidth/2);
        logger->info("Rotating " + std::to_string(ang) + " degrees");
        rotate(ang);
        //setSpeed(forwardSpeed);
    }
}

void PathTask::execute() {
    // Load properties file
    PropertyReader* propReader;
    Properties* settings;
    propReader = new PropertyReader("../src/settings/path_task_settings.txt");
    settings = propReader->load();

    int timeOut = std::stoi(settings->getProperty("TIMEOUT"));
    forwardSpeed = std::stoi(settings->getProperty("FORWARD_SPEED"));

    logger->info("Starting Path Task");

    ///TODO INSERT HSV VALUES HERE
    ImgData* data = dynamic_cast<ImgData*> (dynamic_cast<CameraState*>(cameraModel->getState())->getDeepState("raw"));
    //old hsv settings: 5, 105, 59, 0, 237
    HSVFilter hsvf(14, 33, 0, 231, 102, 255);
    LineFilter lf;
    // looking for 1 rectangle
    ShapeFilter sf(1, 1);

    imgHeight = data->getImg().size().height;
    imgWidth = data->getImg().size().width;

    bool orangeFound = false;
    bool lookAround = false;
    bool lineFound = false;
    bool first = true;

//    cv::namedWindow("hsv", CV_WINDOW_AUTOSIZE);

    Timer timer;
    timer.start();
    while (!done && timer.getTimeElapsed() < timeOut) {
        // If its moving, let it move for a bit then continue the program
        if (moving) {
            usleep (100000);
            moving = false;
            continue;
        }
        delete data;
        data = dynamic_cast<ImgData*> (dynamic_cast<CameraState*>(cameraModel->getState())->getDeepState("raw"));
        hsvf.filter(data);

        //cv::imshow("hsv", data->getImg());

        if (!orangeFound) {
            // Step 1: look for orange, if found, turn to follow it

            // Look for orange
            std::vector<cv::Point2f> massCenters = sf.findMassCenter(data->getImg());
            if (massCenters.size() > 0) {
                logger->info("Found orange.  Moving to orange mass");
                // Move to orange
                moveTo(massCenters.at(0));
            } else {
                // If no orange found, move forwards
                logger->debug("No orange mass found");
                setSpeed(forwardSpeed);
            }

            // If we see lines, then move to step 2
            bool lines = lf.filter(data);
            bool rect = sf.filter(data);
            if (lines || rect) {
                orangeFound = true;
                if (lines) {
                    logger->info("Found lines from orange segmentation");
                }
                if (rect) {
                    logger->info("Found rectange from orange segmentation");
                }
            }
        } else if (lookAround) {
            // Step 3 (Panning): if parallel lines couldnt be found
            // look 45 degrees left, then 90 degrees right (45 from start)
            // if still cant find anything, then move forward then repeat

            logger->info("Panning");
            setSpeed(forwardSpeed);
            // 0 = found lines; 0 = false
            if (!lf.filter(data)) {
                // pauses whatever it's doing and goes back to looking for lines
                lookAround = false;
            }
            if (timer.getTimeElapsed() > timeOut) {
                done = true;
                logger->info("Failed to find path");
                // FAILED TO LOOK FOR PATH
            }
        } else {
            // Step 2: follow the lines found
            if (sf.filter(data)) {
                // Check for rectangles
                logger->info("Rectangle found");
                cv::RotatedRect rr = sf.getRect()[0];
                //moveTo(rr.center);
                if (first) {
                    logger->info("Stopping");
                    setSpeed(-forwardSpeed);
                    usleep(2000000);
                    setSpeed(0);
                    first = false;
                }
                usleep(500000);
                if (std::abs((int)std::round(rr.angle)) % 90 < std::stoi(settings->getProperty("RECTANGLE_ANGLE_THRESHOLD"))) {
                    logger->info("Aligned with rectangle.  Moving forward");
                    setSpeed(forwardSpeed);
                } else {
                    logger->info("Trying to align to rectangle");
                    rotate(rr.angle);
                    usleep(5000000);
                }
            } else {
                // Not tested yet
                // Check for lines
                logger->debug("Looking for lines");
                lf.filter(data);
                std::vector<std::vector<float>> align(2);
                std::vector<std::vector<float>> allLines = lf.getlineEq();
                bool brk = false;
                bool alignment = false;
                for (unsigned int i = 0; i < allLines.size(); i++) {
                    //find 2 lines with parallel slope, and follow them
                    //if 2 lines horizontal, rotate 90 degrees
                    //if 1 line horizontal, start ///not sure if needed

                    //see horz line -> horizInSight = true
                    //no see horz line anymore -> horzInSight = false, startPath = true
                    //see horz line agian -> horzInSight = true
                    //no see horz line -> finPath = true;
                    //go straight in all of 4 above statements

                    for (unsigned int n = i; n < allLines.size(); n++) {
                        // check the difference in slope
                        //TODO: Change this line to divide the slopes instead of subtract.  Do error checking for infinity and divide by zero
                        float temp;
                        try{
                            if (allLines[i][0] == INFINITY || allLines[n][0] == INFINITY
                                    || allLines[n][0] == 0){
                                temp = 5;
                            }else
                                temp = std::abs(allLines[i][0] / allLines[n][0] - 1);
                        }catch (...){
                            logger->debug("Error");
                            temp = 5;
                        }

                        // vertical lines or aprox parallel slope
                        if ((allLines[i][0] == INFINITY && allLines[n][0] == INFINITY)
                                || temp < 0.05){
                            align[0] = allLines[i];
                            align[1] = allLines[n];
                            brk = true;
                            alignment = true;
                            break;
                        }
                    }
                    if (brk) {
                        break;
                    }
                    lookAround = true;
                }
                // executed once 2 parallel lines are found
                if (alignment) {
                    logger->debug("Current slope of " + std::to_string(align[0][0]));
                    if (fabs(align[0][0]) > 99) {      // 999 = big slope value = vert line
                        // if the average of the 2 x positions are within a threshold, move forward
                        float avg = (align[0][2] + align[1][2]) / 2;
                        if (std::abs(avg) < alignThreshold) {
                            //the sub is aligned with the path
                            setSpeed(50);
                            logger->debug("Done");
                            done = true;
                        } else {
                            //dont have to specifiy left or right cus avg is already the x position
                            //rotate (atan2(imgHeight/4*3, avg-imgWidth/2) * 180/M_PI);
                            setSpeed(forwardSpeed);
                            /*
                        if (avg < imgWidth/2) {  //TODO: Figure out left side value
                            rotate (atan2(avg, imgHeight/4*3) * 180/M_PI);
//                            move("Left", avg / 3);
                        } else {
                            rotate (atan2(avg, imgHeight/4*3) * 180/M_PI);
//                            move("Right", avg / 3);
                        }*/
                        }
                    } else {
                        //normal line
                        if (align[0][0] > 0)    //positive slope, align to the right side
                            rotate(-(atan(align[0][0]) * 180 / M_PI - 90));//takes any slope gets angle (negative because of how sub looks at axes
                        else {                    //negative slope, align to the left side
                            rotate(-(atan(align[0][0]) * 180 / M_PI + 90));
                        }
                    }
                    lineFound = true;
                }
            }
        }
        usleep(33000);    //sleep for 33ms -> act 30 times/sec

    }
    logger->info("Path Task complete");
}
