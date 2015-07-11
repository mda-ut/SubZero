#include "BuoyTask.h"

BuoyTask::BuoyTask(CameraModel* camModel)
{
    this->camModel = camModel;
}

void move(int d){

}

void rise(int d){

}

void rotate(int t){

}

void BuoyTask::execute(){
    ImgData* data = dynamic_cast<ImgData*>(camModel->getState("raw"));
    HSVFilter green (0, 155, 0, 255, 0,255);
    HSVFilter red (0 ,155,0,255,0,255);
    //only look for 1 circle
    ShapeFilter sf (2, 1);
    float imgWidth = data->getImg().size().width;
    float imgHeight = data->getImg().size().height;

    //assuming the sub is in the correct position
    //first look for green, and then hit it
    //then look and hit red

    bool hitGreen = false;
    bool hitRed = false;

    int retreat = 0;

    bool done = false;

    while (!done){
        //filter for a color depending if the other color is hit or not
        if (!hitGreen)
            green.filter(data);
        else if (!hitRed)
            red.filter(data);
        else if (hitGreen && hitRed){
            done = true;
            continue;
        }

        //after hitting a color, move the sub back to look for the other one
        //TODO: CALIBRATE THIS STEP
        if (retreat > 0){
            move(-40);
            retreat -= 1;
            continue;
        }

        if (sf.filter(data)){
            cv::Point2f cent = sf.getCenter()[0];
            if (std::abs(cent.x - imgWidth/2) < imgWidth/5){
                //in the middle 20% of the screen horzontally
                if (std::abs(cent.y - imgHeight/2) < imgHeight/5){
                    //in the middle 20% vertically

                    //move straight and hit it
                    move(40);

                    //if the radius of the circle is huge, so the sub will hit it
                    if (sf.getRad()[0] > imgWidth*imgHeight/3){
                        if (!hitGreen)
                            hitGreen = true;
                        else
                            hitRed = true;

                        //return the sub back to its orginal position
                        move(0);
                        retreat = 30;
                    }
                }
                else{
                    rise (cent.y - imgHeight/2);
                }
            }else{
                rotate(atan2(0, cent.x-imgWidth/2));
            }
        }else{
            //CIRCLES NOT FOUND
            //ROTATE/MOVE SUB
            rotate(45);
        }
    }
}
