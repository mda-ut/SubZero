#include "PortalTask.h"

PortalTask::PortalTask(CameraModel* camModel)
{
    this->camModel = camModel;
    // Load properties file
    PropertyReader* propReader;
    propReader = new PropertyReader("../src/settings/portal_task_settings.txt");
    settings = propReader->load();

    thresh = std::stof(settings->getProperty("thresh"));
    angleThresh = std::stof(settings->getProperty("angleThresh"));
    travelTime = std::stof(settings->getProperty("travelTime"));
    travelDist = std::stof(settings->getProperty("travelDist"));
}

void PortalTask::rotate(float t){

}

void PortalTask::rise(float h){

}

void PortalTask::move(float d){
    float time = travelTime;   //500ms; 0.5s
    float acel = 1;     //need to measure aceleration
    float moveAmount = 0.5f * acel * time * time;
    //FPGAMove (moveAmount);
    //d = vt + 1/2 *a*t^2
}

float getDistanace(float imgWidth, float boxWidth, float realWidth){
    //distance(mm) = realHeight (mm) * imageHeight(px) / objectHeight(px) *
    //      focalLength(mm)/sensorHeight(mm)
    //focalLength/sensorHeight = constant (hopefully)
    float CONS = 0.8524426745;
    return imgWidth / boxWidth * realWidth * CONS;
}

void PortalTask::slide(float d){
    //distance is all in cm
    float hyp = travelDist; //50cm
    float theta = asin(d/hyp) * 180/M_PI;
    rotate(theta);
    move(-hyp);
    rotate(-theta);
    move(hyp);
}


float PortalTask::calcPixScale(std::vector<cv::RotatedRect> rekts){
    //calculate pixScale
    int v1 = -1, v2 = -1;
    int h1 = -1;
    for (unsigned int i = 1; i < rekts.size(); i++){
        for (unsigned int n = 0; n < i; n++){
            if (std::abs(rekts[i].angle - rekts[n].angle) < angleThresh){
                v1 = i;
                v2 = n;
                h1 = 3 - i + n; //0+1+2 = 3, this finds the remaining index
            }
        }
    }
    //if it didnt find 3 rectangles, use the longer rectangle and approx pixScale
    if (v1 == -1){
        if (rekts.size() == 1)      //cant approximaate with just 1 rectangle, go next
            return -1;

        //find the longest sides from the 2 rectangles
        float max1 = 0, max2 = 0;
        if (rekts[0].size.width > rekts[0].size.height)
            max1 = rekts[0].size.width;
        else
            max1 = rekts[0].size.height;

        if (rekts[1].size.width > rekts[1].size.height)
            max2 = rekts[1].size.width;
        else
            max2 = rekts[1].size.height;

        //make sure max2 is the longest side
        if (max1 > max2){
            float temp = max1;
            max1 = max2;
            max2 = temp;
        }

        bool good1 = false, good2 = false;
        //check the scale aginst the other
        //if the difference isnt that bad, use it
        good1 = std::abs(120/max1 * max2 - 240) < thresh;
        good2 = std::abs(240/max2 * max1 - 120) < thresh;

        if (good1 && good2)
            //if both scales are good, then average the 2 values
            return (120/max1 + 240/max2)/2;
        else if (good1)
            return 120/max1;
        else if (good2)
            return 240/max2;
        else
            //if none of the 2 are good, gg go next
            return -1;
    }else{
        //todo, if it reaches here its not guaranteed to be 3 rectangles
        //find pixScale values from all 3, and test it on each other
        float height1 = 0, height2 = 0;
        float width1 = 0;

        //make sure those values are the max
        if (rekts[v1].size.width > rekts[v1].size.height)
            height1 = rekts[v1].size.width;
        else
            height1 = rekts[v1].size.height;
        if (rekts[v2].size.width > rekts[v2].size.height)
            height2 = rekts[v2].size.width;
        else
            height2 = rekts[v2].size.height;
        if (rekts[h1].size.width > rekts[h1].size.height)
            width1 = rekts[h1].size.width;
        else
            width1 = rekts[h1].size.height;

        std::vector<bool> guci(3);
        std::vector<float> pix(3);
        pix[0] = 120/height1;
        pix[1] = 120/height2;
        pix[2] = 240/width1;

        guci[0] = std::abs(pix[0]*height2 - 120) < thresh && std::abs(pix[0]*width1 - 240) < thresh;
        guci[1] = std::abs(pix[1]*height1 - 120) < thresh && std::abs(pix[1]*width1 - 240) < thresh;
        guci[2] = std::abs(pix[0]*height1 - 120) < thresh && std::abs(pix[2]*height2 - 120) < thresh;
        if (guci[0] && guci[1] && guci[2]){
            //if all 3 are good, then take average of the 3
            return (pix[0]+pix[1]+pix[2])/3;
        }else if (!guci[0] && !guci[1] && !guci[2])
            //if none are good, then rip
            return -1;          //if all 3 are false, gnext

            //look for 2 good ones, then take average of it
        for(int i=0; i < 3; i++){
            for(int n=0; n<3; n++){
                if (n == i)
                    continue;
                if (guci[i] && guci[n]){
                    return (pix[i]+pix[n])/2;
                }
            }
        }
        //if it still didnt find anything, take it from 1 value
        for (int i = 0; i < 3; i++)
            if (guci[i])
                    return pix[i];
    }
    return -1;
}

void PortalTask::execute() {

    bool redMode = settings->getProperty("RED_MODE") == "TRUE";
    bool yellowMode = settings->getProperty("YELLOW_MODE") == "TRUE";

    std::stof(settings->getProperty("travelDist"));
    //TODO calibrate hsv
    HSVFilter red(std::stoi(settings->getProperty("red1")),
                  std::stoi(settings->getProperty("red2")),
                  std::stoi(settings->getProperty("red3")),
                  std::stoi(settings->getProperty("red4")),
                  std::stoi(settings->getProperty("red5")),
                  std::stoi(settings->getProperty("red6")));
    ShapeFilter redRect (1, 1);
    ImgData* redData = 0;

    HSVFilter yellow(std::stoi(settings->getProperty("y1")),
                  std::stoi(settings->getProperty("y2")),
                  std::stoi(settings->getProperty("y3")),
                  std::stoi(settings->getProperty("y4")),
                  std::stoi(settings->getProperty("y5")),
                  std::stoi(settings->getProperty("y6")));
    ShapeFilter yRekt (1, 3);
    ImgData* yellowData = 0;

    float imgWidth;
    float imgHeight;

    int forwardSleep = std::stoi(settings->getProperty("forwardSleep"));
    int lowHeight = std::stoi(settings->getProperty("lowHeight"));
    int highHeight = std::stoi(settings->getProperty("highHeight"));
    int backupDist = std::stoi(settings->getProperty("backupDist"));


    //first allign with the red tube,
    //with the yellow tubes at the side and bottom
    //then keep moving forward and hope it remains straight in the tube
    bool done = false;
    bool forward = false;

    float pixScale;     // cm/pix ratio

    //bool redMode = false, yellowMode = true;
    bool foundRed = false, foundYellow = false;
    while (!done){        
        std::string s = "raw";
        ImgData* data = dynamic_cast<ImgData*>
                (dynamic_cast<CameraState*>
                 (camModel->getState())->getState(s));
        imgWidth = data->getImg().size().width;
        imgHeight = data->getImg().size().height;
        redData = new ImgData(*data);
        yellowData = new ImgData(*data);

        if (forward){
            //sleep(forwardSleep);   //or however long it takes to travel 2.5m
            done = true;
            continue;
        }

        if (redMode){
            red.filter(redData);
            foundRed = redRect.filter(redData);
        }

        yellow.filter(yellowData);
        foundYellow = yRekt.filter(yellowData);     //TODO, change filter to boolean
        pixScale = 0;                               //TODO, not reset every iteraiton

        //if found a red rectangle
        if (redMode && foundRed){
            cv::RotatedRect rr = redRect.getRect()[0];
            //if the rectangle is in the middle of the screen
            if (std::abs(rr.center.x - imgWidth/2) < imgWidth/5){

                pixScale = calcPixScale(yRekt.getRect());

                //float y = rr.center.y - imgHeight/10 * 3;
                float y = rr.center.y * pixScale;

                //if the sub is bewteen 70 and 100cm above the red rectangle
                if (lowHeight < y && y < highHeight)
                    forward = true;
                else
                    //rise the difference between the difference
                    rise((rr.center.y - imgHeight) * pixScale);
            }
            //if rectangle is not in the middle
            else{
                //allign with rectangle
                float distance;     //distance in cm
                float deltaX = rr.center.x - imgWidth/2;
                if (foundYellow){
                    pixScale = calcPixScale(yRekt.getRect());
                }else{
                    //if there are no yellow rectangles for some reason, go and hope for the best with the red one
                    //this should never be reached

                    //the longer side is the width, which is 30cm
                    if (rr.size.width > rr.size.height)
                        pixScale = 30/rr.size.width;
                    else
                        pixScale = 30/rr.size.height;
                }
                distance = deltaX * pixScale;
                slide(distance);
            }
        }
        //check for yellow rectangles for size comparison
        //avg height of 2 rectangles / pixle repreentation
        // = m/pix of image, use that on horizontal to allign
        else if (foundYellow && yellowMode){
            //if the red rectangle isnt found but yellow is
            //calculate pixScale, the allign to the x middle, ~30/40% y
            std::vector<cv::RotatedRect> rekts = yRekt.getRect();
            int v1 = -1, v2 = -1;
            int h1 = -1;
            bool brk = false;
            for (unsigned int i = 1; i < rekts.size(); i++){
                for (unsigned int n = 0; n < i; n++){
                    if (std::abs(rekts[i].angle - rekts[n].angle) < thresh){
                        v1 = i;
                        v2 = n;
                        h1 = 3 - i + n; //0+1+2 = 3
                        brk = true;
                        break;
                    }
                    if (brk)
                        break;
                }
            }
            pixScale = calcPixScale(rekts);
            //if it didnt find 3 rectangles
            if (v1 == -1){
                //figure out which one is the horziontal one
                float avgX = 0;
                //if the angle works, this is the horizontal one
                //just take the center of it and move towards it
                if (std::abs(rekts[0].angle - 90) < angleThresh)      //TODO test angles
                    avgX = rekts[0].center.x;
                else if (std::abs(rekts[1].angle - 90) < angleThresh)      //TODO test angles
                    avgX = rekts[1].center.x;
                else        //2 vertical rectangles
                    avgX = (rekts[0].center.x + rekts[1].center.x)/2;

                if (std::abs(avgX - imgWidth/2) < 20/pixScale){
                    //if the sub is in 20cm of the middle
                    yellowMode = false;
                    redMode = true;
                }else
                    slide ((avgX - imgWidth/2) * pixScale);
            }else{
                //allign the sub to the middle
                float avgX1 = 0, avgX2 = 0;
                avgX1 = (rekts[v1].center.x + rekts[v2].center.x) /2;
                //avgX2 = rekts[h1].center.x;
                //float dif = std::abs(avgX1 - avgX2);
                //if (dif > imgWidth/4){}
//                    //idk what to do here, TODO
//                float avgX = (avgX1+avgX2)/2;

                if (std::abs(avgX1 - imgWidth/2) < 20/pixScale){
                    //if the sub is in 20cm of the middle
                    yellowMode = false;
                    redMode = true;
                }else
                    slide ((avgX1 - imgWidth/2) * pixScale);

                //move the sub in y direction, make the yellow bottom in the bottom ~30% of screen
                float y = rekts[h1].center.y - imgHeight/10 * 3;
                y /= pixScale;
                //y -= 75;    //the bottom rectangle should be 75cm below the middle

                //rise 3/4 the difference between the difference
                rise(y/4*3);
            }
        }else{
            //if it sees no red or yellow
            move(backupDist);
        }

        delete redData;
        delete yellowData;
        redData=0;
        yellowData=0;
    }

}
