#include "CompetitionView.h"


CompetitionView::CompetitionView(Stage* stage, Controller *controller) {
    this->controller = controller;
    this->stage = stage;
}

void CompetitionView::initialize() {
  taskThread = std::thread(&CompetitionView::startCompetitionRun, this);
}

void CompetitionView::startCompetitionRun() {
  usleep(5000000); // wait for model to finish initializing
  emit controller->runCompetition(); 
}

void CompetitionView::update(int ID) {
    // Nothing to do
}
