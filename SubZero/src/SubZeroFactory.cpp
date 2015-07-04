/*
 * SubZeroFactory.cpp
 *
 *  Created on: May 25, 2015
 *      Author: carl
 */

#include "SubZeroFactory.h"
#include "CameraModel.h"
#include "CameraInterface.h"
#include "CameraState.h"
#include "FPGAModel.h"
#include "FPGAInterface.h"
#include "FPGAState.h"
#include "ShowCaseView.h"
#include "Controller.h"
#include <vector>
#include <iostream>

SubZeroFactory::SubZeroFactory() {
	// TODO Auto-generated constructor stub

}

SubZeroFactory::~SubZeroFactory() {
	// TODO Auto-generated destructor stub
    delete logger;
}

SubZero* SubZeroFactory::makeSubZero(SubType subType, PropertyReader* settings) {
    std::vector<Model*> models;
    std::vector<State*> states;
    View* view;
    Controller* controller;
    //TODO: Add error checking for property file reading
    logger->trace(std::to_string(std::stoi(settings->getProperty("CAM_BUFFER_SIZE"))));
    int camBufferSize = std::stoi(settings->getProperty("CAM_BUFFER_SIZE"));
    int camPollFrequency = std::stoi(settings->getProperty("CAM_POLL_FREQUENCY"));
    int fpgaBufferSize = std::stoi(settings->getProperty("FPGA_BUFFER_SIZE"));
    int fpgaPollFrequency = std::stoi(settings->getProperty("FPGA_POLL_FREQUENCY"));

    switch (subType) {
    case GUI: {
		//TODO SubZero has models, which needs States, FMs, and Interfaces, which need filters? and observers? which needs View, which needs Controller, which needs Model?
		std::cout << "guisub" << std::endl;

        states.push_back(new CameraState(FRONTCAM));
        states.push_back(new CameraState(DOWNCAM));
        states.push_back(new FPGAState(FPGA));
        view = new ShowCaseView(states);

        for (auto& state : states) {
            state->addViewer(view);
        }

        int frontCamPos = std::stoi(settings->getProperty("FRONT_CAM"));
        int downCamPos = std::stoi(settings->getProperty("DOWN_CAM"));
        HwInterface* frontCamInt = new CameraInterface(camBufferSize,camPollFrequency,frontCamPos);
        HwInterface* downCamInt = new CameraInterface(camBufferSize,camPollFrequency,downCamPos);
        HwInterface* fpgaInt = new FPGAInterface(fpgaBufferSize, fpgaPollFrequency);

        models.push_back(new CameraModel(states[0], frontCamInt));
        models.push_back(new CameraModel(states[1], downCamInt));
        models.push_back(new FPGAModel(states[2], fpgaInt));

        controller = new Controller(models, view);

        break;
    }
	case SIM:
		std::cout << "simsub" << std::endl;
		break;
	case AUT:
		std::cout << "autsub" << std::endl;
		break;
	default:
		std::cout << "unrecognized sub type: " << subType << std::endl;
        break;
	}

    SubZero* sub = new SubZero(models, view, controller);
    return sub;
}

