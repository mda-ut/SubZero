/*
 * CameraInterface.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef CAMERAINTERFACE_H_
#define CAMERAINTERFACE_H_

#include "HwInterface.h"
#include "DataDefinition.h"
// include other camera + image specific classes
// #include "ImageInputProcessor.h"
// #include "ImageFormatter.h"
// #inlcude "CamIntrinsic.h" //stores camera intrinsic parameters

enum CameraPosition {
  FRONT,
  DOWN
};


/**
 * A child of HwInterface that deals specifically with the camera. Concrete class.
 */

class CameraInterface: public HwInterface {

private:

    /* 
     * private helper function for send
     * enocde data to be sent to hardware
     * encode the msg at pointer Mat src (source)
     * output results to location at pointer ImgData des(tination) 
     */
    virtual int encode(Mat* src, ImgData* des); 
    
    /*
     * this class will be automatically pulling and managing
     * the pulling process privately within the interface
     * using the following functions
     */
    virtual int pullTo(Mat* des); // pull raw data from hardware at pullFrequency to des(tination) as specified
    virtual int decode(Mat* src, ImgData* des); // decode the Mat at src and store at ImgData des(tination)

protected:

    virtual int deleteFromBuffer(int startIdx, int endIdx); // delete from startIdx to endIdx inclusively
    virtual int storeToBuffer(ImgData* src); // store decoded data at src to buffer

public:

    virtual int copyFromBuffer(int startIdx, int endIdx, ImgData** src); // copy from [startIdx, endIdx]
    virtual int send(ImgData* src); // send data at src to hardware indicated by hardwareID   

    /*
     * getters and setters for the private fields
     */
    virtual int getPullFrequency();
    virtual int setPullFrequency(int frequency);
    virtual int getBufferSize();
    virtual int setBufferSize(int bufferSize);
    
    /*
     * constructors and destructors
     */
    FPGAInterface(int bufferSize, int pullFrequency, int policy, int hardwareID);
    virtual ~FPGAInterface();

};


#endif 


/* CAMERAINTERFACE_H_ */