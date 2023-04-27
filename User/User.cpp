//
// Created by Pawel Biniak on 18/03/2023.
//

#include "User.h"

User::User(size_t time, Network* network, Agenda* agenda, size_t id, double speed, double location) : Process(time, network, agenda),
	id_(id),
	speed_(speed),
	currentLocation_(location),
	currentBaseStation(BaseStation::BS1),
	powerReceivedBS1_(0),
	powerReceivedBS2_(0),
	connected_(true),
	timeToTrigger_(Constants::timeToTriggerStartValue) {
	this->setPowerReceived();
}

User::~User() = default;

void User::execute() {
	bool active = true;
	while (active) {
		switch (state_) {
			case State::GENERATE_USER:
				network_->addUserToNetwork(this);
				// Zaplanowanie następnego usera który ma być dodany do systemu
				{
					auto new_id = id_ + 1;
					auto new_user = new User(time_, network_, agenda_, new_id, Constants::v(), Constants::x);
					new_user->activate(rand() % 25);
				}
				state_ = State::REPORT_POWER;
				break;
			case State::REPORT_POWER:
				// pobieranie mocy z BS1 i BS2
				this->setPowerReceived();

				// sprawdzamy warunek alfa (czy handover)
				if (this->alphaCondition()) {
					state_ = State::HANDOVER;
				}
				// sprawdzamy warunek czy user jest w odległości x od stacji BS2 (wtedy ma być rozłączenie)
				else if (this->distanceCondition()) {
					state_ = State::REMOVE_USER;
					Process::setTerminated();
					active = false;
				}
				// sprawdzamy warunek delta czyli czy user ma być od razu rozłączony
				else if (this->deltaCondition()) {
					state_ = State::REMOVE_USER;
					active = false;
				}
				else {
					active = false;
					timeToTrigger_ = Constants::timeToTriggerStartValue;
				}

				// jeśli żaden z warunków nie jest spełniony to odkładamy usera za 20ms i przesuwany go w systemie
				Process::activate(20);
				this->move();
				break;
			case State::HANDOVER:
				timeToTrigger_ -= 20;
				if (timeToTrigger_ == 0) {
					Process::activate(20);
					state_ = State::CHANGE_STATION;
				}
				break;
			case State::CHANGE_STATION:
				currentBaseStation = BaseStation::BS2;
				// po zmianie stacji, następny stan to report_power i odkładamy usera na 20ms
				state_ = State::REPORT_POWER;
				Process::activate(20);
				active = false;
				break;
			case State::REMOVE_USER:
				// wake up next process/user in buffer in current time
				network_->getBufferFirst()->activate(time_, false);
				Process::setTerminated();
				break;
		}
	}
}

void User::setPowerReceived() {
	powerReceivedBS1_ = 4.56 - 22 * std::log10(currentLocation_) + Constants::s();
	powerReceivedBS2_ = 4.56 - 22 * std::log10(currentLocation_) + Constants::s();
}

// If true start counting until handover
bool User::alphaCondition() const {
	return powerReceivedBS2_ - powerReceivedBS1_ > Constants::alfa;
}

// If true disconnect user :(
bool User::deltaCondition() const {
	return powerReceivedBS1_ < powerReceivedBS2_ - Constants::delta;
}

// If true change station
bool User::distanceCondition() const {
	return currentLocation_ >= 3000;
}

void User::move() {
	currentLocation_ += speed_;
}

size_t User::getId() const {
	return id_;
}
