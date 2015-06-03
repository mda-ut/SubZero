/*
 * StateTester.cpp
 *
 *  Created on: May 30, 2015
 *      Author: james
 */
/*
 * Class to test state functions
 * @author James
 *
 */
#include "StateTester.h"

ImgData* StateTester::generateImgData(std::string id, std::string msg){
	cv::Mat *m = new cv::Mat(10, 10, 2);
	ImgData *d = new ImgData(id, m);
	d->setMsg(msg);
	return d;
}

std::vector<ImgData*> StateTester::generateImgVector(int i){
	std::vector<ImgData*> vec;
	if (i == 1){
		vec.push_back(generateImgData("First", "msg1"));
		vec.push_back(generateImgData("Second", "msg2"));
		vec.push_back(generateImgData("Third", "msg3"));
	}else if (i == 2){
		vec.push_back(generateImgData("1", "one"));
		vec.push_back(generateImgData("2", "two"));
		vec.push_back(generateImgData("3", "three"));
		vec.push_back(generateImgData("4", "four"));
		vec.push_back(generateImgData("5", "five"));
		vec.push_back(generateImgData("6", "six"));
		vec.push_back(generateImgData("7", "seven"));
		vec.push_back(generateImgData("8", "eight"));
		vec.push_back(generateImgData("9", "nine"));
		vec.push_back(generateImgData("10", "ten"));
	}
	else{

	}
	return vec;
}

std::string StateTester::testBasics(){
	CameraState cs;

	cs.setState(generateImgVector(1));
	//Logger::trace("Generated Image Vector");
	Logger::trace(cs.getState("First")->getMsg());
	return "True";
}

std::string StateTester::testSize(){
	CameraState cs(8);

	cs.setState(generateImgVector(1));
	for (int i = 0; i < 7; i++){
		cs.setState(generateImgVector(2));
	}

	Logger::trace(cs.getState("First", 7)->getMsg());
	cs.setState(generateImgVector(2));
	Logger::trace(cs.getState("First", 8)->getMsg());
	cs.setState(generateImgVector(2));
	Logger::trace(cs.getState("First", 9)->getMsg());
	return "True";
}

void StateTester::run(){
	StateTester st;
	Logger::trace("===========Starting State Testing===========");

	Logger::trace("-----Testing basics-----");
	Logger::trace("-----Basics: " + st.testBasics() + "-----");

	Logger::trace("-----Testing size-----");
	Logger::trace("-----Size: " + st.testSize() + "-----");

	Logger::trace("============End State Testing===============");
}

