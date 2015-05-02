/*
 * State.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: James
 */


State::State() {
	init();
}

State::State(int framesStored) {
	init();
	maxLength = framesStored;

}

State::~State() {
	delete stateData;
}

void State::init(){
	frameStarted = false;
	stateData = new std::list<std::vector<Data*>>;

}

Data* getState (std::string ID, int i){


}


Data* getState (std::string ID){



	for (Data* data: State::stateData){

	}


	for (int x = 0; x < 5; x++){

	}

}
