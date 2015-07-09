#include "Stage.h"

Stage::Stage(QWidget *parent) : QWidget(parent) {
   currentView = nullptr;
}

void Stage::initialize() {
   //TODO: Initialize any parameters
}

void Stage::setViewContent(View* view) {
   if (currentView != nullptr) {
       logger->info("Deleting previous view");
       // Delete and disconnects all associated QWidgets and their respective signals and slots
       delete currentView;
   }
   currentView = view;
   currentView->setParent(this);
   currentView->initialize();
   currentView->show();
   logger->info("New View initialized");
}

Stage::~Stage() {
    delete logger;
}
