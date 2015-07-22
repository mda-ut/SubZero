/*
 * SubZeroFactory.cpp
 *
 *  Created on: May 25, 2015
 *      Author: carl
 */

#include "SubZeroFactory.h"
#include "CameraModel.h"
#include "SimCameraInterface.h"
#include "CameraInterface.h"
#include "CameraState.h"
#include "FPGAModel.h"
#include "FPGAInterface.h"
#include "FPGAState.h"
#include "MenuView.h"
#include "GUIView.h"
#include "Controller.h"
#include "SimFPGA.h"
#include "SimFPGAInterface.h"
#include "SimBufferWindow.h"
#include <vector>
#include <iostream>

SubZeroFactory::SubZeroFactory(Properties* settings) {
    this->settings = settings;
    stage = nullptr;
}

SubZeroFactory::~SubZeroFactory() {
    delete settings;
    delete logger;
}

void SubZeroFactory::setStage(Stage* newStage) {
    stage = newStage;
}

SubZero* SubZeroFactory::makeSubZero(std::string subType) {
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

    if (subType == "MENU") {
        controller = new Controller(models);
        view = new MenuView(stage);
    } else if (subType == "GUI") {
        logger->trace("Creating GUI sub");

        states.push_back(new CameraState(FRONTCAM, camBufferSize));
        //states.push_back(new CameraState(DOWNCAM, camBufferSize));
        //states.push_back(new FPGAState(FPGA, fpgaBufferSize));

        int frontCamPos = std::stoi(settings->getProperty("FRONT_CAM"));
        int downCamPos = std::stoi(settings->getProperty("DOWN_CAM"));
        HwInterface* frontCamInt = new CameraInterface(frontCamPos);
        //HwInterface* downCamInt = new CameraInterface(downCamPos);
//        HwInterface* fpgaInt = new SimFPGAInterface(settings, new SimFPGA(settings));

        models.push_back(new CameraModel(states[0], frontCamInt, camPollFrequency));
//        models.push_back(new CameraModel(states[1], downCamInt, camPollFrequency));
//        models.push_back(new FPGAModel(states[2], fpgaInt, fpgaPollFrequency));

        controller = new Controller(models);
        view = new GUIView(stage, controller, states);
        controller->setView(view);

        for (auto& state : states) {
            state->addViewer(view);
        }
    } else if (subType == "SIMULATOR") {
        logger->trace("Creating simulation sub");
        Qt3D::QEntity* rootEntity = new Qt3D::QEntity();
        SimulatedSub* simSub = new SimulatedSub(rootEntity);
        SimulatedEnvironment* simEnv = new SimulatedEnvironment(rootEntity);

        states.push_back(new CameraState(FRONTCAM, camBufferSize));
        states.push_back(new CameraState(DOWNCAM, camBufferSize));
        states.push_back(new FPGAState(FPGA, fpgaBufferSize));

        SimFPGA* simFPGA = new SimFPGA(settings, simSub);
        SimBufferWindow* bufferWindow = new SimBufferWindow(simSub, simEnv, rootEntity);
        int frontCamPos = std::stoi(settings->getProperty("FRONT_CAM"));
        int downCamPos = std::stoi(settings->getProperty("DOWN_CAM"));

        HwInterface* frontCamInt = new SimCameraInterface(frontCamPos, bufferWindow);
        HwInterface* downCamInt = new CameraInterface(downCamPos);
        HwInterface* fpgaInt = new SimFPGAInterface(settings, simFPGA);

        models.push_back(new CameraModel(states[0], frontCamInt, camPollFrequency));
        models.push_back(new CameraModel(states[1], downCamInt, camPollFrequency));
        models.push_back(new FPGAModel(states[2], fpgaInt, fpgaPollFrequency));

        controller = new Controller(models);
        view = new GUIView(stage, controller, states);

        controller->setView(view);

        for (auto& state : states) {
            state->addViewer(view);
        }
    } else if (subType == "AUTONOMOUS") {
        logger->trace("Creating autonomous sub");
    } else {
        logger->error("Unrecognized sub type " + subType);
	}

    SubZero* sub = new SubZero(models, view, controller);
    return sub;
}

