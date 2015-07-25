#include "CompetitionView.h"

CompetitionView::CompetitionView() {

}

CompetitionView::CompetitionView(Controller *controller) {
    this->controller = controller;
}

void CompetitionView::initialize() {
    emit controller->runCompetition();
}

void CompetitionView::update(int ID) {
    // Nothing to do
}
