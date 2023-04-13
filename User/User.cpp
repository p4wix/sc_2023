//
// Created by Pawel Biniak on 18/03/2023.
//

#include "User.h"
#include "../Constants/Constants.h"

/*
User::User(size_t id, size_t time, Network* network, Agenda* agenda, double speed_, double location) :
	Process(time, network, agenda), id_(id), speed(speed_), currentLocation(location) {
	this->powerReceivedBS1 = 0;
	this->powerReceivedBS2 = 0;
	this->connected = true;
	this->timeToTrigger = Constants::timeToTriggerStartValue;
}
 */

User::User(double speed_, double location) : speed(speed_), currentLocation(location) {
	this->powerReceivedBS1 = 0;
	this->powerReceivedBS2 = 0;
	this->connected = true;
	this->timeToTrigger = Constants::timeToTriggerStartValue;
}

User::~User() = default;

void User::setPowerReceived() {
	powerReceivedBS1 = 4.56 - 22 * std::log10(currentLocation) + Constants::s();
	powerReceivedBS2 = 4.56 - 22 * std::log10(currentLocation) + Constants::s();
}

void User::handleAlfaCondition() {
	if(powerReceivedBS2 - powerReceivedBS1 > Constants::alfa) {
		timeToTrigger -= 20;
	}
	else {
		timeToTrigger = Constants::timeToTriggerStartValue;
	}
}

void User::handleChangeStation() {
	if(timeToTrigger == 0) {
		// Przełączenie stacji
		// I pytanie czy tu też następuje rozłączenie użytkownika???
	}
}

void User::handleHandover() {
	this->handleAlfaCondition();
	this->handleChangeStation();
}

void User::move() {
	currentLocation += speed;
}

void User::disconnectByPoorConnection() {
	double x = powerReceivedBS2 - Constants::delta;
	if(powerReceivedBS1 < x) {
		this->disconnect();
	}
}

void User::disconnectByDistanceReached() {
	if(currentLocation >= 3000) {
		this->disconnect();
	}
}

void User::disconnect() {
	connected = false;
}

size_t User::getId() const {
	return id_;
}
