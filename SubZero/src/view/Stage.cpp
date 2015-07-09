#include "Stage.h"

Stage::Stage(QWidget *parent) : QWidget(parent) {
    currentView = nullptr;
    stageLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
}

void Stage::initialize() {
    this->setLayout(stageLayout);
    this->show();
}

void Stage::setViewContent(View* view) {
    if (currentView != nullptr) {
        logger->info("Deleting previous view");
        stageLayout->removeWidget(currentView);
        // Delete and disconnects all associated QWidgets and their respective signals and slots
        delete currentView;
    }
    currentView = view;
    currentView->initialize();
    stageLayout->addWidget(currentView);
    logger->info("New View initialized");
}

QSize Stage::sizeHint() const {
    return currentView->sizeHint();
}

QSize Stage::minimumSizeHint() const {
    return currentView->minimumSizeHint();
}

Stage::~Stage() {
    delete logger;
    delete stageLayout;
}
