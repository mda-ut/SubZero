#include "Stage.h"

Stage::Stage(QWidget *parent, SubZeroFactory* subZeroFactory) : QWidget(parent) {
    this->subZeroFactory = subZeroFactory;
    subZeroFactory->setStage(this);
    subZero = nullptr;
    stageLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    stageLayout->setSizeConstraint(QLayout::SetFixedSize);
}

void Stage::initialize() {
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->setLayout(stageLayout);
    this->show();
}

void Stage::setViewContent(std::string type) {
    if (subZero != nullptr && subZero->getView() != nullptr) {
        logger->info("Deleting previous view");
        stageLayout->removeWidget(subZero->getView());
        // Delete SubZero instance
        // Delete and disconnects all associated QWidgets and their respective signals and slots
        delete subZero;
    }
    subZero = subZeroFactory->makeSubZero(type);
    subZero->initialize();
    stageLayout->addWidget(subZero->getView());
    this->show();
    logger->info("New View initialized");
}

QSize Stage::sizeHint() const {
    return subZero->getView()->sizeHint();
}

QSize Stage::minimumSizeHint() const {
    return subZero->getView()->minimumSizeHint();
}

void Stage::switchToGUIView() {
    setViewContent("GUI");
}

void Stage::switchToSimulatorView() {
    setViewContent("SIMULATOR");
}

void Stage::switchToMenuView() {
    setViewContent("MENU");
}

void Stage::exit() {
    if (subZero->getView() != nullptr) {
        subZero->getView()->close();
        stageLayout->removeWidget(subZero->getView());
        logger->debug("Removed View");
    }
    close();
}

Stage::~Stage() {
//    if (subZero->getView() != nullptr) {
//        stageLayout->removeWidget(subZero->getView());
//        logger->debug("Removed View");
//    }
    delete stageLayout;
    if (subZero != nullptr) {
        delete subZero;
        logger->debug("Deleted SubZero");
    }
    delete subZeroFactory;
    delete logger;
}
