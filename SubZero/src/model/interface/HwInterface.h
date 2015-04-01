/*
 * HwInterface.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef HWINTERFACE_H_
#define HWINTERFACE_H_

#include "Data.h"
// Data is the generic datatype defined in Data.h


/**
 * HwInterface is an abstract class responsible for all the io interfacing with hardware.
 */
class HwInterface {

private:
    
    /*
     * pointer to memory allocated for storing raw (but 
     * decoded) data from hardware
     */
    Data** decodedBuffer[]; 

    /* allocate only enough memory to keep a max of 
     * this number of hardware inputs; discard all after that
     */
    int bufferSize; 

    /* 
     * pull data from hardware at this frequency
     */
    int pullFrequency;

    /* 
     * this value specifies the encoding, decoding policy to use
     * alternatively, we can just implement encode(), decode() ... etc
     * differently for each hardwares when we branch out 
     * from our abstract class
     */
    int policy;

    /* 
     * id of hardware this interface interacts with
     * hardware can be accessed (somehow) via this ID
     */
    int hardwareID;

    /* 
     * private helper function for send
     * enocde data to be sent to hardware
     * encode the msg at pointer Data src (source)
     * output results to location at pointer Data des(tination) 
     */
    virtual int encode(Data* src, Data* des); 
    
    /*
     * this class will be automatically pulling and managing
     * the pulling process privately within the interface
     * using the following functions
     */
    virtual int pullTo(Data* des); // pull raw data from hardware at pullFrequency to Data destination specified
    virtual int decode(); // decode the data at src and store at Data des(tination)

protected:

    virtual int deleteFromBuffer(int startIdx, int endIdx); // delete from startIdx to endIdx inclusively
    virtual int storeToBuffer(Data* src); // store decoded data at src to buffer

public:

    virtual int copyFromBuffer(Data* des); // copy most recent one to des
    virtual int copyFromBuffer(int startIdx, int endIdx, Data** des); // copy from [startIdx, endIdx]
    virtual int send(Data* src); // send data at src to hardware indicated by hardwareID   

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
    virtual HwInterface(int bufferSize, int pullFrequency, int policy, int hardwareID);
    virtual ~HwInterface();

};


#endif 


/* HWINTERFACE_H_ */
