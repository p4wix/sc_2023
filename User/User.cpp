//
// Created by Pawel Biniak on 18/03/2023.
//

#include "User.h"

User::User(size_t time, Network* network, Agenda* agenda, size_t id, double speed, double location) : Process(time, network, agenda),
	id_(id),
	speed_(speed),
	currentLocation_(location),
	powerReceivedBS1_(0),
	powerReceivedBS2_(0),
	connected_(true),
	timeToTrigger_(Constants::timeToTriggerStartValue) { }

User::~User() = default;

void User::execute() {
	Process::execute();
}

void User::setPowerReceived() {
	powerReceivedBS1_ = 4.56 - 22 * std::log10(currentLocation_) + Constants::s();
	powerReceivedBS2_ = 4.56 - 22 * std::log10(currentLocation_) + Constants::s();
}

void User::handleAlfaCondition() {
	if(powerReceivedBS2_ - powerReceivedBS1_ > Constants::alfa) {
		timeToTrigger_ -= 20;
	}
	else {
		timeToTrigger_ = Constants::timeToTriggerStartValue;
	}
}

void User::handleChangeStation() {
	if(timeToTrigger_ == 0) {
		// Przełączenie stacji
		// I pytanie czy tu też następuje rozłączenie użytkownika???
	}
}

void User::handleHandover() {
	this->handleAlfaCondition();
	this->handleChangeStation();
}

void User::move() {
	currentLocation_ += speed_;
}

void User::disconnectByPoorConnection() {
	double x = powerReceivedBS2_ - Constants::delta;
	if(powerReceivedBS1_ < x) {
		this->disconnect();
	}
}

void User::disconnectByDistanceReached() {
	if(currentLocation_ >= 3000) {
		this->disconnect();
	}
}

void User::disconnect() {
	connected_ = false;
}

size_t User::getId() const {
	return id_;
}