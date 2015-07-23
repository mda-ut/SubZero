/*
 * State.cpp

 *
 *  Created on: Apr 20, 2015
 *      Author: James
 */
#include "State.h"
#include "View.h"

State::State(int stateID, uint32_t bufferSize) {
    this->stateID = stateID;
    this->bufferSize = bufferSize;
    frameStarted = false;
}

State::~State() {
    delete logger;
}

void State::addViewer(View* viewer) {
    connect(this, SIGNAL(notifyViewers(int)), viewer, SLOT(update(int)));
    logger->info("Viewer added");
}

/*
Data* State::getState (std::string ID, int i){
    if (i > stateData.size()){
        std::cout << "NULL" << std::endl;
        return NULL;				//index out of range
    }

    std::list<std::vector<Data*> >::reverse_iterator it = stateData.rbegin();
    std::advance(it, i);		//advance the list to the ith position

    for (Data* data: *it){
        if (data->getID().compare(ID) == 0){
            return data;	//return deep copy
        }
    }
    return 0;
}

Data* State::getState (std::string ID){
    std::vector<Data*> temp = this->stateData.back();

    for (Data* data: temp){
        if (data->getID().compare(ID) == 0){
            return data;		//need to make a deep copy then return it
        }
    }

    std::cout << "NULL2" << std::endl;
    return 0;
}

Data* State::getRaw(int i){
    return this->getState("RAW", i);
}

Data* State::getRaw(){
    return this->getState("RAW");
}
*/
