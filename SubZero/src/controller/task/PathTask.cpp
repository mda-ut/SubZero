#include "PathTask.h"

#include <math.h>

PathTask::PathTask() {
    startPath = false;
    finPath = false;
    done = false;
    horzInSight = false;
    inlineThresh = 75;
}

PathTask::PathTask(Model* cameraModel, TurnTask *turnTask, SpeedTask *speedTask) {
    this->cameraModel = dynamic_cast<CameraModel*>(cameraModel);
    this->turnTask = turnTask;
    this->speedTask = speedTask;

    startPath = false;
    finPath = false;
    done = false;
    horzInSight = false;
    inlineThresh = 75;
}

PathTask::~PathTask(){
    delete logger;
}

void PathTask::println(std::string s){
    if (debug)
        logger->info(s);
}

bool moving = false;
void PathTask::move(float amount) {
    speedTask->setTargetSpeed(amount);
    speedTask->execute();
    moving = true;
}
void PathTask::stop(){
    moving = false;
    // Stop
    speedTask->setTargetSpeed(0);
    speedTask->execute();
}

void PathTask::rotate(float angle) {
    logger->debug("Rotating sub by " + std::to_string(angle) + " degrees");
    turnTask->setYawDelta(angle);
    turnTask->execute();
    usleep(7000000);
}

void PathTask::moveTo(cv::Point2f pos) {
    // pretty much in line
    if (std::abs(pos.x-imgWidth/2) < inlineThresh) {
        //float distance = std::sqrt(pos.x * pos.x + pos.y * pos.y);
        if (pos.y - imgHeight/2 > 0) {
            println("MoveTo moving forward");
            move(30);
        } else {
            println("MoveTo moving backwards");
            move(-30);
        }
    } else {
        float ang = atan2(pos.y-imgHeight/2, pos.x-imgWidth/2) * 180 / M_PI;
        println("MoveTo rotating " + std::to_string(ang));
        rotate(ang);
        move(30);
    }
}

void PathTask::execute() {
    // Load properties file
    PropertyReader* propReader;
    Properties* settings;
    propReader = new PropertyReader("../SubZero/src/settings/path_task_settings.txt");
    settings = propReader->load();

    int timeOut = std::stoi(settings->getProperty("TIMEOUT"));

    ///TODO INSERT HSV VALUES HERE
    ImgData* data = dynamic_cast<ImgData*> (dynamic_cast<CameraState*>(cameraModel->getState())->getDeepState("raw"));
    HSVFilter hsvf(30, 152, 75, 255, 100, 255);
    LineFilter lf;
    //looking for 1 rectangle
    ShapeFilter sf(1, 1);
    imgHeight = data->getImg().size().height;
    imgWidth = data->getImg().size().width;

    bool foundOrange = false;
    bool lookAround = false;
    bool foundLine = false;

    float angle = 0;
    float amount = 0;
    //float timeOut = 0;
    int stage = 0;
    cv::namedWindow("hsv", CV_WINDOW_AUTOSIZE);
    while (!done) {
        //if its moving, let it move for a bit then continue the program

        if (moving) {
            usleep (100000);
            moving = false;
            continue;
        }
        delete data;
        data = dynamic_cast<ImgData*> (dynamic_cast<CameraState*>(cameraModel->getState())->getDeepState("raw"));
        hsvf.filter(data);

        cv::imshow("hsv", data->getImg());

        if (!foundOrange) {
            // Step 1: look for orange, if found, turn to follow it

            //if sees lines, then move to step 2
            if (lf.filter(data)) {
                foundOrange = true;
                println("Found lines from orange");
                continue;
            }

            //look and turn to orange
            std::vector<cv::Point2f> massCenters = sf.findMassCenter(data->getImg());
            if (massCenters.size() > 0) {
                println("found orange");
                moveTo(massCenters.at(0));
            }else{
                //if dont see orange, move forwards
                move(30);
            }

        } else if (lookAround) {
            // Step 3; if parallel lines couldnt be found
            // look 45 degrees left, then 90 degrees right (45 from start)
            // if still cant find anything, then move forward then repeat

            /*
            if (angle <= -45) {
                // bounce back from -45° in 3 frames
                stage = 1;
                // -1 to avoid any floating point errors
                amount = -(angle - 1) / 3;
                rotate(amount);
                angle += amount;
            } else if (stage == 1 && std::abs(angle) < 5) {
                // center itself back to 0°
                stage = 2;
                rotate(-angle);
                angle = 0;
            } else if (angle >= 45) {
                // bounce back from 45° in 3 frames
                stage = 3;
                amount = -(angle + 1) / 3;
                rotate(amount);
                angle += amount;
            } else if (stage == 3 && std::abs(angle) < 5) {
                // center itself again
                rotate(-angle);
                angle = 0;
                stage = 4;
            }

            if (stage == 0) {
                // look left 5 degrees at a time
                rotate(-5);
                angle += -5;
            } else if (stage == 1 || stage == 3) {
                // bouncing back to 0°
                rotate(amount);
                angle += amount;
            } else if (stage == 2) {
                // look right 5° at a time
                rotate(5);
                angle += 5;
            } else if (stage == 4 && !foundLine) {
                // if nothing was found after everything, move forward and try again
                move(30);
                stage = 0;
            }
*/
            println("moving forwards, step 3");
            move(30);
            timeOut++;
            // 0 = found lines; 0 = false
            if (!lf.filter(data)) {
                //pauses whaterver its doing and go back to look for lines
                lookAround = false;
                //reset values
                angle = 0;
                stage = 0;
                timeOut = 0;
            }
            if (timeOut > 30*5){
                done = true;
                println("Failed to find path");
                //FAILED TO LOOK FOR PATH
            }
        } else {
            // Step 2, follow the lines found
            lf.filter(data);
            println("Passed lines");
            std::vector<std::vector<float>> align(2);
            std::vector<std::vector<float>> allLines = lf.getlineEq();
            bool brk = false;
            bool allignment = false;
            for (unsigned int i = 0; i < allLines.size(); i++) {
                //find 2 lines with parallel slope, and follow them
                //if 2 lines horizontal, rotate 90 degrees
                //if 1 line horizontal, start ///not sure if needed

                //see horz line -> horizInSight = true
                //no see horz line anymore -> horzInSight = false, startPath = true
                //see horz line agian -> horzInSight = true
                //no see horz line -> finPath = true;
                //go straight in all of 4 above statements

                for (unsigned int n = i; n < allLines.size(); n++){
                    // check the difference in slope
                    float temp = std::abs(allLines[i][0] - allLines[n][0]);
                    // vertical lines or aprox parallel slope
                    if ((allLines[i][0] == INFINITY && allLines[n][0] == INFINITY)
                            || temp < 20){
                        align[0] = allLines[i];
                        align[1] = allLines[n];
                        brk = true;
                        allignment = true;
                        break;
                    }
                }
                if (brk)
                    break;
                lookAround = true;

            }
            // executed once 2 parallel lines are found
            if (allignment) {
                logger->debug("Current slope of " + std::to_string(align[0][0]));
                if (fabs(align[0][0]) > 99) {      // 999 = big slope value = vert line
                    // if the average of the 2 x positions are within a threshold, move forward
                    float avg = (align[0][2] + align[1][2]) / 2;
                    if (std::abs(avg) < inlineThresh) {
                        //the sub is aligned with the path
                        move(50);
                        println("Done");
                        done = true;
                    } else {
                        //dont have to specifiy left or right cus avg is already the x position
                        //rotate (atan2(imgHeight/4*3, avg-imgWidth/2) * 180/M_PI);
                        move(30);
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
                    //float avgB = (align[0][1] + align[1][1]) / 2;
                    //float x = 0;
                    if (align[0][0] > 0)    //positive slope, align to the right side
                        //x = imgWidth/4 * 3;
                        rotate(-(atan(align[0][0])*180/M_PI - 90));//takes any slope gets angle (negative because of how sub looks at axes
                    else {                    //negative slope, align to the left side
                        //x = imgWidth/4;
                        rotate(-(atan(align[0][0])*180/M_PI + 90));
                    }
                    //float y = align[0][0] * x + avgB;
                    //rotate(atan2(y-imgHeight/2, x) * 180 / M_PI);
                }
                foundLine = true;
            }
        }
        usleep(33000);    //sleep for 33ms -> act 30 times/sec

    }
}
