#include "BuoyTask.h"

BuoyTask::BuoyTask(CameraModel* camModel)
{
    this->camModel = camModel;

    // Load properties file
    PropertyReader* propReader;
    propReader = new PropertyReader("../SubZero/src/settings/buoy_task_settings.txt");
    settings = propReader->load();
    travelDist = std::stoi(settings->getProperty("g5"));
}

void BuoyTask::move(float d){

}

void BuoyTask::rise(float h){

}

void BuoyTask::rotate(float t){

}
void BuoyTask::slide(float d){
    //distance is all in cm
    float hyp = travelDist; //50cm
    float theta = asin(d/hyp) * 180 / M_PI;
    deltaAngle = theta;
    rotate(theta);
    move(-hyp);
    rotate(-theta);
    move(hyp);
}

float BuoyTask::calcDistance(float rad){
    //distance(mm) = realHeight (mm) * imageHeight(px) / objectHeight(px) *
    //      focalLength(mm)/sensorHeight(mm)
    //focalLength/sensorHeight = constant (hopefully)
    float CONSY = 1.0400192063;
    float CONSX = 0.8524426745;

    return (imgHeight/rad * 23 * CONSY +
            imgWidth/rad * 23 * CONSX)/2;
}

void BuoyTask::execute() {

    HSVFilter green(std::stoi(settings->getProperty("g1")),
                  std::stoi(settings->getProperty("g2")),
                  std::stoi(settings->getProperty("g3")),
                  std::stoi(settings->getProperty("g4")),
                  std::stoi(settings->getProperty("g5")),
                  std::stoi(settings->getProperty("g6")));

    HSVFilter red(std::stoi(settings->getProperty("r1")),
                  std::stoi(settings->getProperty("r2")),
                  std::stoi(settings->getProperty("r3")),
                  std::stoi(settings->getProperty("r4")),
                  std::stoi(settings->getProperty("r5")),
                  std::stoi(settings->getProperty("r6")));
    //only look for 1 circle
    ShapeFilter sf (2, 1);

    //assuming the sub is in the correct position
    //first look for green, and then hit it
    //then look and hit red

    bool hitGreen = false;
    bool hitRed = false;

    int retreat = 0;
    int moveDist = std::stoi(settings->getProperty("moveDist"));
    int rotateAng = std::stoi(settings->getProperty("rotateAng"));
    int movementDelay = std::stoi(settings->getProperty("movementDelay"));
    int deltaDist = 0;

    bool done = false;

    while (!done){
        std::string s = "raw";
        ImgData* data = dynamic_cast<ImgData*>
                (dynamic_cast<CameraState*>
                 (camModel->getState())->getDeepState(s));
        imgWidth = data->getImg().size().width;
        imgHeight = data->getImg().size().height;

        //filter for a color depending if the other color is hit or not
        if (!hitRed)
            red.filter(data);
        else if (!hitGreen)
            green.filter(data);
        else if (hitGreen && hitRed){
            done = true;
            continue;
        }

        //after hitting a color, move the sub back to look for the other one
        //TODO: CALIBRATE THIS STEP
        if (retreat){
            move(-deltaDist - 20);      //move 20cm more than i needed
            //sleep(movementDelay);
            //move the sub back to the middle
            if (deltaAngle != -1){
                rotate(deltaAngle);
                move (deltaDist-20);   //move 20cm less than i need
                rotate(-deltaAngle);
            }
            retreat = false;
            continue;
        }

        if (sf.filter(data)){
            cv::Point2f cent = sf.getCenter()[0];
            if (std::abs(cent.x - imgWidth/2) < imgWidth/5){
                //in the middle 20% of the screen horzontally
                if (std::abs(cent.y - imgHeight/2) < imgHeight/5){
                    //in the middle 20% vertically

                    //if the radius of the circle is huge, so the sub will hit it
                    if (sf.getRad()[0] > imgWidth*imgHeight/3){
                        if (!hitGreen)
                            hitGreen = true;
                        else
                            hitRed = true;

                        //return the sub back to its orginal position
                        move(0);
                        retreat = true;
                    }else{
                        //move straight and hit it
                        float dist = calcDistance(sf.getRad()[0]);
                        deltaDist = dist*1.2;
                        move(deltaDist);
                    }
                }
                else{
                    rise (cent.y - imgHeight/2);
                }
            }else{
                //rotate(atan2(0, cent.x-imgWidth/2) * 180 / M_PI);
                float scale = 23/sf.getRad()[0];
                float dist = sf.getCenter()[0].x - imgWidth/2;

                //slide 2/3 of the way
                slide(dist * scale/3*2);
            }
        }else{
            //CIRCLES NOT FOUND
            //ROTATE/MOVE SUB
            //rotate(rotateAng);
            move(moveDist);
        }
        delete data;
        data = 0;
    }
}
