#include "PathTask.h"

PathTask::PathTask()
{

}

void move(std::string direction, float amount){
}

void rotate(float angle){   //rotate angle degrees cw
}

float inlineThresh = 75;

void moveTo(cv::Point2f pos){
    if (std::abs(pos.x) < inlineThresh){  //pretty much in line
        float distance = std::sqrt(pos.x*pos.x + pos.y*pos.y);
        if (pos.y > 0){
            move("Forward", distance/4);
        }else{
            move("Backward", distance/4);
        }
    }
    else{
        rotate(atan2(pos.x, pos.y) * 180/PI);
    }
}

void PathTask::execute(CameraState* s){
    //fix with proper structure
    ImgData* data = s->getState("hsv");
    LineFilter lf;
    ShapeFilter sf(1, 1);

    bool foundOrange = false;
    bool lookAround = false;
    bool foundLine = false;

    float angle = 0;
    float amount = 0;
    int stage = 0;
    while (1){
        // step 1; look for orange, if sees it, turn to follow it
        if (!foundOrange){
            std::vector<cv::Point2f> massCenters = sf.findMassCenter(data->getImg());
            if (massCenters.size() > 0){
                moveTo(massCenters.at(0));
            }

            if (lf.filter(data)){
                foundOrange = true;
            }
        }
        //step 3; if parallel lines couldnt be found
        else if (lookAround){
            //look 45 degrees left, then 90 degrees right (45 from start)
            //if still cant find anything, then move forward then repeat

            //bounce back from -45° in 3 frames
            if (angle <= -45){
                stage = 1;
                //-1 to avoid any floating point errors167
                amount = -(angle-1)/3;
                rotate(amount);
                angle += amount;
            }
            //center itself back to 0°
            else if (stage == 1 && std::abs(angle) < 5){
                stage = 2;
                rotate (-angle);
                angle = 0;
            }
            //bounce back from 45° in 3 frames
            else if (angle >= 45){
                stage = 3;
                amount = -(angle+1)/3;
                rotate (amount);
                angle += amount;
            }
            //center itself agian
            else if (stage == 3 && std::abs(angle) < 5){
                rotate (-angle);
                angle = 0;
                stage = 4;
            }

            //look left 5 degrees at a time
            if (stage == 0){
                rotate (-5);
                angle += -5;
            }
            //bouncing back to 0°
            else if (stage == 1 || stage == 3){
                rotate (amount);
                angle += amount;
            }
            //look right 5° at a time
            else if (stage == 2){
                rotate (5);
                angle += 5;
            }
            //if nothing was found after everything, move forward and try agian
            else if (stage == 4 && !foundLine){
                move("Forward", 50);
                stage = 0;
            }

            if (!lf.filter(data)){  //0 = found lines; 0 = false
                lookAround = false;
            }
        }
        // step 2, follow the lines found
        else{
            lf.filter(data);
            std::vector<std::vector<float>> allign(2);
            std::vector<std::vector<float>> allLines = lf.getlineEq();
            for (unsigned int i = 0; i < allLines.size(); i++){
                //find 2 lines with parallel slope, and follow them
                //if 2 lines horizontal, rotate 90 degrees
                //if 1 line horizontal, start ///not sure if needed

                //see horz line -> horizInSight = true
                //no see horz line anymore -> horzInSight = false, startPath = true
                //see horz line agian -> horzInSight = true
                //no see horz line -> finPath = true;
                //go straight in all of 4 above statements

                for (unsigned int n = i; n < allLines.size(); n++){
                    //check the difference in slope
                    float temp = std::abs(allLines[i][0] - allLines[n][0]);
                    //vertical lines or aprox parallel slope
                    if (temp == NAN || temp < 20){
                        allign[0] = allLines[i];
                        allign[1] = allLines[n];
                        goto allignment;
                    }
                }
                lookAround = true;

            }
            //executed once 2 parallel lines are found
            allignment:{
                if (std::abs(allign[0][0]) < 20){   //horz line
                    rotate(90);         //rotate 90 degrees
                }else if(allign[0][0] > 9999){      //vert line
                    //if the average of the 2 x positions are within a threshold, move forward
                    float avg = (allign[0][2] + allign[1][2]) / 2;
                    if (std::abs(avg) < inlineThresh){
                        move("Forward", 50);
                    }else{
                        if (avg < 0){
                            move("Left", avg/3);
                        }else{
                            move("Right", avg/3);
                        }
                    }
                }else{                              //normal line
                    float avgB = (allign[0][1] + allign[1][1]) / 2;
                    float x = 50;       //can be changed
                    float y = allign[0][0]*x + avgB;
                    rotate(atan2(x, y) * 180/PI);
                }
                foundLine = true;
            }

        }
        //sleep(33);    //sleep for 33ms -> act 30 times/sec
    }

}
