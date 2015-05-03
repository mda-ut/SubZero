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
	this->frameStarted = false;
	this->stateData = new std::list<std::vector<Data*>>;

}

Data* State::getState (std::string ID, int i){
	if (i > stateData.size()){
		return 1;				//index out of range
	}

	auto it = stateData.rbegin();
	std::advance(it, i);		//advance the list to the ith position

	for (Data* data: *it){
		if (&data->ID == ID){
			return data;	//return deep copy
		}
	}
	return 0;
}

Data* State::getState (std::string ID){
	std::vector<Data*> temp = this->stateData.back();

	for (Data* data: temp){
		if (&data->ID == ID){
			return data;		//need to make a deep copy then return it
		}
	}
	return 0;
}

int State::setState(std::vector<Data*> d){
	//this->stateData.insert(d);	//insert vector into list
	return 0;
}

Data* State::getRaw(int i){

}

Data* State::getRaw(){
	std::vector<Data*> temp = this->stateData.back();
	for (Data* data: temp){
		if (&data->ID == "RAW"){
			return data;	//need to change to return deep copy
		}
	}
	return 0;
}
