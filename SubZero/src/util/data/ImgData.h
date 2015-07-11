/*
 * ImgData.h
 *
 *  Created on: Mar 29, 2015
 *      Author: ahsueh1996
 */

#ifndef IMGDATA_H_
#define IMGDATA_H_
#include "Data.h"
#include "opencv2/highgui.hpp"

/**
 * Wrapper class containing a image of the standard image type
 * and functions to get image parameters such as dimensions,
 * and pixel depth. ImgData should only be created by certain
 * classes thus, much like ImgData, the setters are reserved
 * for those privileged classes.
 */
class ImgData: public Data {

	/* =========================================================================
	 * FRIEND CLASSES
	 * =========================================================================
	 */
	friend class RGBFilter;
	friend class HwInterface;

private:

    Logger* logger = new Logger("ImgData");

	/* ==========================================================================
	 * FRIEND FUNCS
	 * ==========================================================================
	 */
	/*
	 * Set function for changing the imgID
	 *
	 * @param new imgID string
	 */
	void setID(std::string newID);

	/* ==========================================================================
	 * CLASS VARS
	 * ==========================================================================
	 */

	/*
	 * String for the named window showing the img
	 */
	std::string windowName;

public:
	/*
	 * Pointer to the actual image object. Mat is the designated standard
	 * image type.
	 */
    cv::Mat img;

	/* ==========================================================================
	 * CONSTRUCTOR & DESTRUCTOR
	 * ==========================================================================
	 */

	/**
	 * Constructor takes in the string ID of the image being created.
	 *
	 * @param ID of the new image
	 * @param the actual image object pointer to be wrapped. Use openCVs Mat.
	 */
    ImgData(std::string dataID,cv::Mat img);

	/**
	 * Destructor stub.
	 */
	virtual ~ImgData();

	/* ==========================================================================
	 * IMG MANIPULATION FUNCS
	 * ==========================================================================
	 */

	/**
	 * Setter for img data. This function will make a copy of the mat img
	 * and set the img variable to point to it. This way the mat img is
	 * within the ImgData obj's scope.
	 *
	 * @param newImg	the pointer to the new Mat obj to wrap
	 */
    void setImg(cv::Mat newImg);

	/**
	 * Getter for img data, invoker must expect the standard image type,
	 * in this case Mat, and will be returned a pointer to the Mat wrapped
	 * by ImgData. Don't delete the img by accident!! Alternatively
	 * directly access the img variable.
	 *
	 * @return standard image pointer.
	 */
    cv::Mat getImg();

	/**
	 * Getter for image height.
	 *
	 * @return int representing the image height.
	 */
	int getHeight();

	/**
	 * Getter for image width.
	 *
	 * @return int representing the image width.
	 */
	int getWidth();

	/**
	 * Attempts to show the Mat img in a new window.
	 */

	void showImg(std::string windowName="");

	/**
	 * Attempts to close the window opened by showImg().
	 */
	void closeImg();

	/* ==========================================================================
	 * OPERATOR OVERLOAD
	 * ==========================================================================
	 */

	/**
	 * The = operator overload that will complete a deep copy of the
	 * right hand side operator and return it.
	 *
	 * @param rhs	the right hand side of the equal operator, the parent copy
	 * @return		address to a new ImgData
	 */
    ImgData& operator=(const ImgData& rhs);

	/**
	 * Copy constructor
	 *
	 * @param obj	the object referenced in the construction
	 */
    ImgData(const ImgData& obj);
};

#endif /* IMGDATA_H_ */
