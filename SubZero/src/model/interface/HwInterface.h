/*
 * HwInterface.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef HWINTERFACE_H_
#define HWINTERFACE_H_

#include "Data.h"
// suppose the following are defined in a separate Data.h
// typedef struct HwData {
	// blah blah 0s and 1s????
// } HwData;

// typedef struct SwData {
	// stuff 
// } SwData;

/**
 * HwInterface is an abstract class responsible for all the io interfacing with hardware.
 */
class HwInterface {

private:
    
    /*
     * pointer to memory allocated for storing raw (but 
     * decoded) data from hardware
     */
    SwData *decodedBuffer[]; 

    /* allocate only enough memory to keep a max of 
     * this number of hardware inputs; discard all after that
     */
    int bufferSize; 

    /* 
     * look at only every this number of inputs
     * i.e. pull data from hardware at this frequency
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

public:

	/* 
	 * enocde data to be sent to hardware
	 * encode the msg at pointer sData
	 * output results to location at pointer hData
	 */
	virtual int encode(SwData *sData, HwData *hData); 
	virtual int send(HwData *hData); // send data to hardware
	virtual int pull(HwData *hData); // pull raw data from hardware at pullFrequency
	virtual int decode(HwData *hData, SwData *sData); // decode the hdata and store at sData
	virtual int storeToBuffer(SwData *sData); // store decoded data to buffer
	virtual int deleteFromBuffer(int startIdx, int endIdx); // delete from startIdx to endIdx inclusively
	virtual int copyFromBufferToState(int startIdx, int endIdx, State *state); // copy from [startIdx, endIdx]
	virtual int getPullFrequency();
	virtual int setPUllFrequency(int frequency);
	virtual int getBufferSize();
	virtual int setBufferSize(int BufferSize);
    virtual HwInterface(int bufferSize, int pullFrequency, int policy, int hardwareID);
	virtual ~HwInterface();

};


#endif 


/* HWINTERFACE_H_ */