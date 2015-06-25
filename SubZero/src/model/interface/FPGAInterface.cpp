/*
 * FPGAInterface.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

//#include "FPGAInterface.h"
//
//
///* ==========================================================================
// * 				INTERACTING WITH DATA COMING IN (FROM FPGA)
// * ==========================================================================
// * This interface class will be automatically polling and managing
// * the polling process privately within the interface at pollFrequency
// * using the functions below.
// */
//
//void FPGAInterface::poll() {
//
//	std::string raw;
//	cin >> raw;
//	Data* decoded = this->decode(&raw);
//	this->storeToBuffer(decoded);
//
//};
//
//FPGAData* FPGAInterface::decode(string* data) {
//
//    std::istringstream iss(data);
//    std::istream_iterator<std::string> begin(iss), end;
//    std::vector<std::string> attributes(begin, end);
//
//    std::string::size_type size;
//
//    // Right now we only have three attributes from FPGA
//    // depth = attributes[0]
//    // speed = attributes[1]
//    // heading = attributes[2]
//    // is it possible to not hardcode this?
//    double depth = std::stod (attributes[0], &size);
//    double speed = std::stod (attributes[1], &size);
//    double heading = std::stod (attributes[2], &size);
//    // Note: for stod (string to double conversion)
//    //       need to compile with -std=c++11
//
//    FPGAData* decoded = new FPGAData("raw", depth, speed, heading);
//
//    return decoded;
//};
//
//
///* ==========================================================================
// * 							MANAGING DATA BUFFER
// * ==========================================================================
// * The data buffer will be managed automatically and privately by this class.
// * These functions are defined and implemented in the root parent class i.e.
// * in HwInterface.
// */
//
//void FPGAInterface::deleteFromBuffer() {
//	this->decodedBuffer.pop();
//};
//
//
//void FPGAInterface::storeToBuffer(Data* data) {
//	this->decodedBuffer.push(data);
//}
//
//void FPGAInterface::in() {
//
//	struct timespec tictoc;
//	clock_gettime(CLOCK_MONOTONIC_RAW, &tictoc);
//
//	while (true) {
//
//		// setting period of polling and auto-clearing
//		// iterate once every this many seconds
//		tictoc.tv_nsec += (long) (1000000000 / pollFrequency);
//		tictoc.tv_sec += (time_t) (tictoc.tv_nsec /pollFrequency);
//		tictoc.tv_nsec %= 1000000000;
//		clock_nanosleep(CLOCK_MONOTONIC_RAW, TIMER_ABSTIME, &tictoc, NULL);
//
//		if ( decodedBuffer.size() >= bufferSize) {
//			// delete old stuff from buffer
//			this->deleteFromBuffer();
//		}
//
//		this->poll();
//
//	}
//}
//
///* ==========================================================================
// * 				INTERACTING WITH DATA GOING OUT (TO FPGA)
// * ==========================================================================
// * FPGAInterface provides functions for the Controller to send data/commands/
// * messages to the FPGA.
// */
//
//void FPGAInterface::set(Attributes attr, int value) {
//	cout << attr << ":" << value << endl;
//}
//
//// for method 2: using libusb
//void FPGAInterface::send(string* data) {
//
//};
//
///* ==========================================================================
// * 								GETTERS AND SETTERS
// * ==========================================================================
// */
//
//Data* FPGAInterface::getDataFromBuffer() {
//	Data* data = new Data("bad");
//	if (! (this->decodedBuffer).empty()) {
//		data = &(this->decodedBuffer.back());
//	} else {
//		std::cout << "Nothing in buffer";
//	}
//	return data;
//};
//
//int FPGAInterface::getPollFrequency() {
//	return this->pollFrequency;
//};
//
//void FPGAInterface::setPollFrequency(int frequency){
//	this->pollFrequency = frequency;
//};
//
//
//int FPGAInterface::getBufferSize(){
//	return this->bufferSize;
//};
//
//void FPGAInterface::setBufferSize(int bufferSize) {
//	this->bufferSize = bufferSize;
//};
//
//
///* ==========================================================================
// * 							CONSTRUCTOR AND DESTRUCTOR
// * ==========================================================================
// */
//
//
//FPGAInterface::FPGAInterface(int bufferSize, int pollFrequency) {
//
//	this->bufferSize = bufferSize;
//	this->pollFrequency = pollFrequency;
//
//	// thread for reading and polling FPGA input
//	// main thread will listen for commands to be sent to FPGA
//	readThread(in);
//
//}
//
//FPGAInterface::~FPGAInterface() {
//
//	// join readThread with main
//	readThread.join();
//
//	// clears the queue
//	while ( ! decodedBuffer.empty()) {
//		decodedBuffer.pop();
//	}
//	// not sure if the above also frees up memory used up by the "queue container"
//	// whatever the container may be... delete it by following the pointer
//	delete &(this->decodedBuffer);
//	delete &(this->bufferSize);
//	delete &(this->pollFrequency);
//
//
//
//}
//
