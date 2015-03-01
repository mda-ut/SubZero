/*
 * HwInterface.h
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#ifndef HWINTERFACE_H_
#define HWINTERFACE_H_

int *[] buffer;

typedef struct HardData {
	// blah blah 0s and 1s????
} HardData;

typedef struct SoftData {
	// stuff 
} SoftData;

class HwInterface {

/**
 * HwInterface is an abstract class responsible for all the io interfacing with hardware.
 */
class HwInterface {

private:
    
    /*
     * pointer to memory allocated for storing raw (but 
     * decoded) data from hardware
     */
    SoftData *decodedBuffer[]; 

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
	int encode(SoftData *sData, HardData *hData); 
	int send(HardData *hData); // send data to hardware
	int pull(HardData *hData); // pull raw data from hardware at pullFrequency
	int decode(HardData *hData, SoftData *sData); // decode the hdata and store at sData
	int storeToBuffer(SoftData *sData); // store decoded data to buffer
	int deleteFromBuffer(int startIdx, int endIdx); // delete from startIdx to endIdx inclusively
	int copyFromBufferToState(int startIdx, int endIdx, State *state); // copy from [startIdx, endIdx]
	int getPullFrequency();
	int setPUllFrequency(int frequency);
	int getBufferSize();
	int setBufferSize(int BufferSize);
    HwInterface:HwInterface(int bufferSize, int pullFrequency, int policy, int hardwareID);
    ~HwInterface();
	HwInterface();
	/**
	 * Constructor
	 */
	virtual ~HwInterface();
	/**
	 * Deconstructor
	 */


};


#endif 


/* HWINTERFACE_H_ */