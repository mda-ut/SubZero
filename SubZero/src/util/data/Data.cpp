/*
 * Data.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: ahsueh1996
 */

#include "Data.h"
//
///* ==========================================================================
// * CONSTRUCTOR & DESTRUCTOR
// * ==========================================================================
// */
//
//Data::Data(std::string dataID) {
//	this->dataID = dataID;
//	this->msg = "";
//}
//
//Data::~Data() {
//}
//
///* ==========================================================================
// * PUBLIC FUNCS COMMON TO ALL CHILDREN
// * ==========================================================================
// */
//
//std::string Data::getID(){
//	return this->dataID;
//}
//
//std::string Data::getMsg(){
//	return this->msg;
//}
//
//int Data::setMsg(std::string newMsg){
//	if (this->msg != "")
//	{
//		this->msg = newMsg;
//		return 1;
//	}
//	this->msg = newMsg;
//	return 0;
//}
//
///* ==========================================================================
// * OPERATOR OVERLOAD
// * ==========================================================================
// */
//
//Data& Data::operator=(Data& rhs) {
//
//	ImgData& ImgCast = (ImgData&) rhs;
//	if (ImgCast != nullptr)
//		return new ImgData(ImgCast);
//
//	FPGAData& FPGACast = (FPGAData&) rhs;
//	if (FPGACast != nullptr)
//		return new FPGAData(FPGACast);
//	return new Data(rhs);
//}
//
//Data::Data(const Data& obj) {
//	this->dataID = obj.getID();
//	this->msg = obj.getMsg();
//}
