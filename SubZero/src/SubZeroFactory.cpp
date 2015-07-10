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
    stage = nullptr;
}

SubZeroFactory::~SubZeroFactory() {
    delete logger;
}

void SubZeroFactory::setStage(Stage* newStage) {
    stage = newStage;
}

SubZero* SubZeroFactory::makeSubZero(std::string subType, Properties* settings) {
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
    case "MENU": {
        view = new MenuView(stage);
    }
    case "GUI": {
        logger->trace("Creating GUI sub");

        states.push_back(new CameraState(FRONTCAM));
//        states.push_back(new CameraState(DOWNCAM));
//        states.push_back(new FPGAState(FPGA));

        int frontCamPos = std::stoi(settings->getProperty("FRONT_CAM"));
        int downCamPos = std::stoi(settings->getProperty("DOWN_CAM"));
        HwInterface* frontCamInt = new CameraInterface(camBufferSize,camPollFrequency,frontCamPos);
//        HwInterface* downCamInt = new CameraInterface(camBufferSize,camPollFrequency,downCamPos);
//        HwInterface* fpgaInt = new FPGAInterface(fpgaBufferSize, fpgaPollFrequency, settings);

        models.push_back(new CameraModel(states[0], frontCamInt));
//        models.push_back(new CameraModel(states[1], downCamInt));
//        models.push_back(new FPGAModel(states[2], fpgaInt));

        controller = new Controller(models);
        view = new GUIView(stage, controller, states);
        controller->setView(view);

        for (auto& state : states) {
            state->addViewer(view);
        }

        break;
    }
    case "SIM":
        logger->trace("Creating simulation sub");
		break;
    case "AUT":
        logger->trace("Creating autonomous sub");
        break;
	default:
        logger->error("Unrecognized sub type " + subType);
        break;
	}

    SubZero* sub = new SubZero(models, view, controller);
    return sub;
}

