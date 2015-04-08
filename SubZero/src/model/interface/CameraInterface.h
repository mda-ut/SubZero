/*
 * CameraInterface.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef CAMERAINTERFACE_H_
#define CAMERAINTERFACE_H_

#include "HwInterface.h"
#include "Data.h"
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
class CameraInterface : public HwInterface {

  private:
    
    /*
     * this class will be automatically pulling and managing
     * the pulling process privately within the interface
     * using the following functions
     */

	/**
	 * Pull raw data from hardware
	 */
    virtual cv::Mat* pull();

    /**
     * Decode the data at src from cv::Mat to ImgData.
   	 */
    virtual ImgData* decode(cv::Mat* src);

  protected:

    /**
     * Delete buffer from startIdx to endIdx
     * @param startIdx, endIdx
     */
    virtual void deleteFromBuffer(int startIdx, int endIdx);


    /**
      * Store decoded data at src to buffer
      * @param src
      */
    virtual void storeToBuffer(Data* src);


  public:

    /**
     * Return the most recent buffer data
     *
     */
    virtual ImgData* getDataFromBuffer();

    /**
     * Return the data in buffer from startIdx to endIdx
     * @param startIdx, endIdx
     */
    @Overload
    virtual ImgData** getDataFromBuffer(int startIdx, int endIdx);

    /**
     * Send data at src to hardware indicated by hardwareID
     * @param src
     */
    virtual void send(Data* src);

    /**
     * Getters and setters for the private fields
     */

    /**
     * Get the frequency of data pulling/polling.
     */
    virtual double getPullFrequency();

    /**
     * Set the frequency of data pulling/polling.
     * @param frequency
     */
    virtual void setPullFrequency(int frequency);

    /**
     * Get size of buffer.
     */
    virtual int getBufferSize();

    /**
     * Set size of buffer.
     */
    virtual void setBufferSize(int bufferSize);

    /**
     * Constructor for Camera Interface
     * @param bufferSize, pullFrequency, policy, hardwareID
     */
    CameraInterface(int bufferSize, int pullFrequency, int policy, int hardwareID);

    /**
     * Destructor
     */
    virtual ~CameraInterface();

};
