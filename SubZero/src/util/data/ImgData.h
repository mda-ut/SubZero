/*
 * ImgData.h
 *
 *  Created on: Mar 29, 2015
 *      Author: ahsueh1996
 */

#ifndef IMGDATA_H_
#define IMGDATA_H_
#include "Data.h"

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
	friend class Filter;
	friend class HwInterface;

private:
	/* ==========================================================================
	 * FRIEND FUNCS
	 * ==========================================================================
	 */

	/**
	 * Constructor takes in the string ID of the image being created.
	 *
	 * @param ID of the new image
	 * @param the actual image object pointer to be wrapped. Use openCVs Mat type.
	 */
	ImgData(std::string ID, cv::Mat* img);

	/**
	 * Destructor stub.
	 */
	virtual ~ImgData();

	/*
	 * Set function for changing the imgID
	 *
	 * @param new imgID string
	 */
	void setImgID(std::string newImgID);

	/**
	 * Setter for replacing the actual image object that a ImgData object
	 * wraps.
	 *
	 * @param pointer to the image object (Mat*)
	 */
	void setImg(cv::Mat* newImg);

	/**
	 * Pointer to the actual image object. Mat is the designated standard
	 * image type.
	 */
	cv::Mat* img;


public:
	/* ==========================================================================
	 * IMG MANIPULATION FUNCS
	 * ==========================================================================
	 */

	/**
	 * Getter for img data, invoker must expect the standard image type,
	 * in this case Mat, and will be returned a pointer to a deep copy
	 * of Mat.
	 *
	 * @return standard image pointer.
	 */
	cv::Mat* getImg();

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
	ImgData& operator=(ImgData& rhs);

	/**
	 * Copy constructor
	 *
	 * @param obj	the object referenced in the construction
	 */
	ImgData(const FPGAData& obj);
};

#endif /* IMGDATA_H_ */
