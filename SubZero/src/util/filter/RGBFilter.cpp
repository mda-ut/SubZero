/*
 * RGBFilter.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: ahsueh1996
 */

#include "RGBFilter.h"

RGBFilter::RGBFilter(int fullspec[]) : Filter() {
	this->setValues(fullspec);
	this->setID("rgbFull");
    PropertyReader* propReader = new PropertyReader("../../SubZero/src/settings/rgbFilter.txt");
    propReader->load();
    //mxColour = std::stoi(propReader->getProperty("RGB_MAX_COLOUR"));
    delete propReader;
}

RGBFilter::RGBFilter(int highlight[], int midtone[], int shadow[]) : Filter() {
	this->setValues(highlight,midtone,shadow);
	this->setID("rgbDiv");
}

RGBFilter::~RGBFilter() {

}


bool RGBFilter::filter(Data* data) {
	// check for whether the input is of the correct type.
	ImgData* cast = dynamic_cast<ImgData*>(data);
	if (cast == 0) {
		// track the error and return error
		this->track(data,this->filterID,1,1);
        return false;
	}

    if (cast->img.type() != 16) {
		this->track(data,this->filterID,2,1);
        return false;
	}

	// begin filter sequence.
	int newPixelVal;
    cv::Mat src = cast->getImg();
    cv::Mat filteredImg = src.clone();
	cv::Mat BGR[3];

	cv::split(filteredImg,BGR);
	// catch error?

	// Full spectrum mode
	if(this->mode == 0) {
        for(int y = 0; y < src.cols; y++ ) {
            for(int x = 0; x < src.rows; x++ ) {
				for(int c = 0; c < 3; c++) {
                    newPixelVal = std::max(0,std::min(mxColour,BGR[c].at<unsigned char>(x,y) + midMult[c]*midtone[c]));
					BGR[c].at<unsigned char>(x,y) = newPixelVal;
				}
			}
		}
	}

	// 3 zone mode
	if (this->mode == 1) {
		int luminosity;
        const int SHADTHRESHOLD = (int) mxColour*10/3;
		const int HIGHTHRESHOLD = SHADTHRESHOLD * 2;
		// get luminosity with some function
		// use luminosity as a switch for case using high, mid or shad
        for(int y = 0; y < src.cols; y++ ) {
            for(int x = 0; x < src.rows; x++ ) {
				// From 11%,59%,30% bgr respectively. Scaled to 1:6:3 factors
				// luminosity range is from 0-2550, 1/3 is 850. Calc this from:
				// 10*255, 10* MXCOLOR
				luminosity = BGR[0].at<unsigned char>(x,y)*1+BGR[1].at<unsigned char>(x,y)*6+BGR[2].at<unsigned char>(x,y)*3;

				for(int c = 0; c < 3; c++) {

					if (luminosity < SHADTHRESHOLD)
                        newPixelVal = std::max(0,std::min(mxColour,BGR[c].at<unsigned char>(x,y) + shadMult[c]*shadow[c]));
					else if (luminosity > HIGHTHRESHOLD)
                        newPixelVal = std::max(0,std::min(mxColour,BGR[c].at<unsigned char>(x,y) + highMult[c]*highlight[c]));
					else
                        newPixelVal = std::max(0,std::min(mxColour,BGR[c].at<unsigned char>(x,y) + midMult[c]*midtone[c]));

					BGR[c].at<unsigned char>(x,y) = newPixelVal;
				}
			}
		}
	}

	//joining seq
	cv::merge(BGR,3,filteredImg);

	//set sequence
    cast->setImg(filteredImg);

	// end sequence.

	// track and return
	this->track(cast,this->filterID,0,0);
    return true;
}

void RGBFilter::setValues(int fullspec[]){
	this->mode = 0;
	this->midMult[0] = (int)((fullspec[2]+.1)/std::abs(fullspec[2]+.1));
    this->midtone[0] = std::max(0,std::min(mxColour,this->midMult[0]*fullspec[2]));
	this->midMult[1] = (int)((fullspec[1]+.1)/std::abs(fullspec[1]+.1));
    this->midtone[1] = std::max(0,std::min(mxColour,this->midMult[1]*fullspec[1]));
	this->midMult[2] = (int)((fullspec[0]+.1)/std::abs(fullspec[0]+.1));
    this->midtone[2] = std::max(0,std::min(mxColour,this->midMult[2]*fullspec[0]));
}

void RGBFilter::setValues(int highlight[], int midtone[], int shadow[]) {
	this->mode = 1;
	this->highMult[0] = (int)((highlight[2]+.1)/std::abs(highlight[2]+.1));
    this->highlight[0] = std::max(0,std::min(mxColour,this->highMult[0]*highlight[2]));
	this->highMult[1] = (int)((highlight[1]+.1)/std::abs(highlight[1]+.1));
    this->highlight[1] = std::max(0,std::min(mxColour,this->highMult[1]*highlight[1]));
	this->highMult[2] = (int)((highlight[0]+.1)/std::abs(highlight[0]+.1));
    this->highlight[2] = std::max(0,std::min(mxColour,this->highMult[2]*highlight[0]));
	this->midMult[0] = (int)((midtone[2]+.1)/std::abs(midtone[2]+.1));
    this->midtone[0] = std::max(0,std::min(mxColour,this->midMult[0]*midtone[2]));
	this->midMult[1] = (int)((midtone[1]+.1)/std::abs(midtone[1]+.1));
    this->midtone[1] = std::max(0,std::min(mxColour,this->midMult[1]*midtone[1]));
	this->midMult[2] = (int)((midtone[0]+.1)/std::abs(midtone[0]+.1));
    this->midtone[2] = std::max(0,std::min(mxColour,this->midMult[2]*midtone[0]));
	this->shadMult[0] = (int)((shadow[2]+.1)/std::abs(shadow[2]+.1));
    this->shadow[0] = std::max(0,std::min(mxColour,this->shadMult[0]*shadow[2]));
	this->shadMult[1] = (int)((shadow[1]+.1)/std::abs(shadow[1]+.1));
    this->shadow[1] = std::max(0,std::min(mxColour,this->shadMult[1]*shadow[1]));
	this->shadMult[2] = (int)((shadow[0]+.1)/std::abs(shadow[0]+.1));
    this->shadow[2] = std::max(0,std::min(mxColour,this->shadMult[2]*shadow[0]));
}

std::vector<int> RGBFilter::getValues() {
	std::vector<int> ret;
	if (mode == 0) {
		ret.push_back(int(this->midtone[2])*midMult[2]);
		ret.push_back(int(this->midtone[1])*midMult[1]);
		ret.push_back(int(this->midtone[0])*midMult[0]);
	} else if (mode == 1) {
		ret.push_back(int(this->highlight[2])*highMult[2]);
		ret.push_back(int(this->highlight[1])*highMult[1]);
		ret.push_back(int(this->highlight[0])*highMult[0]);
		ret.push_back(int(this->midtone[2])*midMult[2]);
		ret.push_back(int(this->midtone[1])*midMult[1]);
		ret.push_back(int(this->midtone[0])*midMult[0]);
		ret.push_back(int(this->shadow[2])*shadMult[2]);
		ret.push_back(int(this->shadow[1])*shadMult[1]);
		ret.push_back(int(this->shadow[0])*shadMult[0]);
	}
	return ret;
}

/* ==========================================================================
 * OPERATOR OVERLOAD
 * ==========================================================================
 */

/*RGBFilter* RGBFilter::operator =(RGBFilter* rhs) {
	return new RGBFilter(rhs);
}


RGBFilter::RGBFilter(RGBFilter* obj) : Filter(obj) {
	this->mode = obj->mode;
	this->highlight[0] = obj->highlight[0];
	this->highlight[1] = obj->highlight[1];
	this->highlight[2] = obj->highlight[2];
	this->midtone[0] = obj->midtone[0];
	this->midtone[1] = obj->midtone[1];
	this->midtone[2] = obj->midtone[2];
	this->shadow[0] = obj->shadow[0];
	this->shadow[1] = obj->shadow[1];
	this->shadow[2] = obj->shadow[2];
}
*/

