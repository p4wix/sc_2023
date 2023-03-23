//
// Created by Pawel Biniak on 18/03/2023.
//

#include "User.h"
#include "../Constants/Constants.h"

User::User() { }

User::~User() { }

User::User(double x, double v) {
	this->currentLocation = x;
	this->speed = v;
	this->powerReceivedBS1 = 0;
	this->powerReceivedBS2 = 0;
	this->connected = false;
	this->handOverActive;
}

double User::powerReceived() {
	return 4.56 - 22 * std::log10(currentLocation) + Constants::s();
}

void User::checkAlfaCond() {
	if(handOverActive) {

	}
	if(powerReceivedBS2 - powerReceivedBS2 > Constants::alfa && !handOverActive) {

	}
}

void User::updatePosition(double dt) {
	currentLocation += speed * dt;
}

bool User::isConnected() const {
	return connected;
}

void User::connect() {
	connected = true;
}

void User::disconnect() {
	connected = false;
}
