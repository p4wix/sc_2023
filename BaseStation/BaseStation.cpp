//
// Created by Pawel Biniak on 18/03/2023.
//

#include "BaseStation.h"

BaseStation::BaseStation() { }

BaseStation::BaseStation(double position, double alpha, double timeToTrigger) {
	this->position = position;
	this->alpha = alpha;
	this->timeToTrigger = timeToTrigger;
}

BaseStation::~BaseStation() { }

double BaseStation::getPosition() {
	return position;
}

double BaseStation::getAlpha() {
	return alpha;
}

double BaseStation::getTimeToTrigger() {
	return timeToTrigger;
}