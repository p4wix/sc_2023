//
// Created by Pawel Biniak on 18/03/2023.
//

#include "User.h"

User::User(double time, Network* network, Agenda* agenda, int id, double speed, double location,
					 UniformGenerator* speedGenerator_, UniformGenerator* spawnTimeGenerator_,
					 UniformGenerator* powerBaseStationGenerator_, char** argv) :
					 Process(time, network, agenda),
					 id_(id),
					 speed_(speed),
					 currentLocation_(location),
					 currentBaseStation(BaseStation::BS1),
					 powerReceivedBS1_(0.0),
					 powerReceivedBS2_(0.0),
					 timeToTrigger_(Constants::timeToTriggerStartValue),
					 disconnectedByDelta(false),
					 disconnectedByDistance(false),
					 speedGenerator(speedGenerator_),
					 spawnTimeGenerator(spawnTimeGenerator_),
					 powerBaseStationGenerator(powerBaseStationGenerator_),
					 userJoinTime(0.0),
					 userLeaveTime(0.0),
					 argv_(argv)
{
	this->setPowerReceived();
}

void User::execute() {
	bool active = true;
	while (active) {
		switch (state_) {
			case State::GENERATE_USER:
				network_->addUserToNetwork(this);
				{
					auto new_id = id_ + 1;
					auto new_user = new User(time_, network_, agenda_, new_id, speedGenerator->RandScaled(), Constants::x,
																	 speedGenerator, spawnTimeGenerator, powerBaseStationGenerator, argv_);
					new_user->activate(spawnTimeGenerator->RandExp(std::stod(argv_[3])));
				}
				state_ = State::REPORT_POWER;
				break;
			case State::REPORT_POWER:
				this->setPowerReceived();

				if (this->alphaCondition()) {
					timeToTrigger_ -= 20;
					if(timeToTrigger_ == 0) {
						if(currentBaseStation == BaseStation::BS1) {
							currentBaseStation = BaseStation::BS2;
						}
						else currentBaseStation = BaseStation::BS1;
						++howManyTimesUserChangedBaseStation;
						if(network_->numbersOfHandledUsers > 25) {
							network_->sendCurrentUserChangeStationReport(this);
						}
						timeToTrigger_ = std::stoi(argv_[4]);
					}
				}
				else {
					timeToTrigger_ = std::stoi(argv_[4]);
				}
				if (this->distanceCondition()) {
					state_ = State::REMOVE_USER;
					disconnectedByDistance = true;
				}
				if (this->deltaCondition()) {
					state_ = State::REMOVE_USER;
					disconnectedByDelta = true;
				}
				if(state_ != State::REMOVE_USER) {
					Process::activate(Constants::t);
					active = false;
					this->move();
				}
				break;
			case State::REMOVE_USER:
				network_->removeUserFromNetwork(this);
				{
					auto new_id = network_->allUsers + 1;
					auto new_user = new User(time_, network_, agenda_, new_id, speedGenerator->RandScaled(), Constants::x,
																	 speedGenerator, spawnTimeGenerator, powerBaseStationGenerator, argv_);
					new_user->state_ = State::REPORT_POWER;
					//new_user->activate(time_, false);
				}
				network_->decrementWaitingBuffer();
				Process::setTerminated();
				active = false;
				break;
		}
	}
}

int User::userId() {
	return get_id();
}

void User::setPowerReceived() {
	powerReceivedBS1_ = 4.56 - 22 * std::log10(currentLocation_) + powerBaseStationGenerator->RandGauss(0, 4).first;
	powerReceivedBS2_ = 4.56 - 22 * std::log10(currentLocation_) + powerBaseStationGenerator->RandGauss(0, 4).second;
}

bool User::alphaCondition() const {
	return currentBaseStation == BaseStation::BS1 ? powerReceivedBS2_ - powerReceivedBS1_ >= Constants::alfa :
	powerReceivedBS1_ - powerReceivedBS2_ >= Constants::alfa;
}

bool User::deltaCondition() const {
	return currentBaseStation == BaseStation::BS1 ? powerReceivedBS1_ - powerReceivedBS2_ >= Constants::delta :
	powerReceivedBS2_ - powerReceivedBS1_ >= Constants::delta;
}

bool User::distanceCondition() const {
	return currentLocation_ >= 3000;
}

void User::move() {
	currentLocation_ += speed_ * Constants::t ; // metry na sekunde
}

int User::get_id() const {
	return id_;
}

double User::get_current_location() const {
	return currentLocation_;
}

double User::get_how_many_times_base_changed() const {
	return howManyTimesUserChangedBaseStation;
}

bool User::get_distance_disc() const {
	return disconnectedByDistance;
}

bool User::get_delta_disc() const {
	return disconnectedByDelta;
}

void User::setUserJoinTime(double time) {
	userJoinTime = time;
}

void User::setUserLeaveTime(double time) {
	userLeaveTime = time;
}

double User::get_user_time_in_network() const {
	return userLeaveTime - userJoinTime;
}

double User::get_user_join_time() const {
	return userJoinTime;
}

double User::get_user_speed() const {
	return speed_;
}
