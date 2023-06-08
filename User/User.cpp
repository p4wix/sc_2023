//
// Created by Pawel Biniak on 18/03/2023.
//

#include "User.h"

User::User(double time, Network* network, Agenda* agenda, int id, double speed, double location,
					 UniformGenerator* speedGenerator_, UniformGenerator* spawnTimeGenerator_, UniformGenerator* powerBaseStationGenerator_) :
	Process(time, network, agenda),
	id_(id),
	speed_(speed),
	currentLocation_(location),
	currentBaseStation(BaseStation::BS1),
	powerReceivedBS1_(0),
	powerReceivedBS2_(0),
	timeToTrigger_(Constants::timeToTriggerStartValue),
	timeToNextRaport(Constants::t),
	speedGenerator(speedGenerator_),
	spawnTimeGenerator(spawnTimeGenerator_),
	powerBaseStationGenerator(powerBaseStationGenerator_)
{
	this->setPowerReceived();
}

void User::execute() {
	bool active = true;
	while (active) {
		switch (state_) {
			case State::GENERATE_USER:
				network_->addUserToNetwork(this);
				if(!network_->isUsersLimitReached){
					auto new_id = id_ + 1;
					auto new_user = new User(time_, network_, agenda_, new_id, speedGenerator->RandScaled(), Constants::x,
																	 speedGenerator, spawnTimeGenerator, powerBaseStationGenerator);
					new_user->activate(spawnTimeGenerator->RandExp(Constants::lambda));
				}
				state_ = State::REPORT_POWER;
				break;
			case State::REPORT_POWER:
				this->setPowerReceived();

				if (this->alphaCondition()) {
					timeToTrigger_ -= 20;
					if(timeToTrigger_ == 0) {
						if(currentBaseStation == BaseStation::BS1) currentBaseStation = BaseStation::BS2;
						else currentBaseStation = BaseStation::BS1;
						++howManyTimesUserChangedBaseStation;
						timeToTrigger_ = Constants::timeToTriggerStartValue;
					}
				}
				else {
					timeToTrigger_ = Constants::timeToTriggerStartValue;
				}
				if (this->distanceCondition()) {
					state_ = State::REMOVE_USER;
				}
				if (this->deltaCondition()) {
					state_ = State::REMOVE_USER;
				}
				if(state_ != State::REMOVE_USER) {
					Process::activate(20);
					active = false;
					this->move();
				}
				break;
			case State::REMOVE_USER:
				network_->removeUserFromNetwork(this);
				if(!network_->isWaitingBufforEmpty()){
					// wake up, pierwszy process który jest uśpiony w kolejce waitingBuffor
					network_->getBufforLastElement()->setWaitingFalseAndActive(time_);
					network_->removeWaitingBufforFirstUser();
				}
				Process::setTerminated();
				active = false;
				break;
		}
	}
}

void User::setPowerReceived() {
	powerReceivedBS1_ = 4.56 - 22 * std::log(currentLocation_) + powerBaseStationGenerator->RandGauss(0, 4).first;
	powerReceivedBS2_ = 4.56 - 22 * std::log(currentLocation_) + powerBaseStationGenerator->RandGauss(0, 4).second;
}

bool User::alphaCondition() const {
	return currentBaseStation == BaseStation::BS1 ? powerReceivedBS2_ - powerReceivedBS1_ >= Constants::alfa : powerReceivedBS1_ - powerReceivedBS2_ >= Constants::alfa;
}

bool User::deltaCondition() const {
	return currentBaseStation == BaseStation::BS1 ? powerReceivedBS1_ - powerReceivedBS2_ >= Constants::delta : powerReceivedBS2_ - powerReceivedBS1_ >= Constants::delta;
}

bool User::distanceCondition() const {
	return currentLocation_ >= 3000;
}

void User::move() {
	currentLocation_ += speed_;
}

int User::get_id() const {
	return id_;
}

void User::sentUserReport(std::fstream& file) {
	std::stringstream csvLine;

	if (file.tellg() == 0) {
		// File is empty, write column titles
		file << "Time, User Id, Buffer Size, Waiting Buffer Size, How many times user changed base station\n";
	}

	csvLine << Process::get_time() << ',' << id_ << ',' << network_->get_buffer_size() << ','
					<< network_->get_waiting_buffer_size() << ',' << howManyTimesUserChangedBaseStation << '\n';

	file << csvLine.str();
}