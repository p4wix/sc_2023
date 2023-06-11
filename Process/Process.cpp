//
// Created by Pawel Biniak on 13/04/2023.
//

#include "Process.h"

Process::Process(double time, Network* network, Agenda *agenda) : time_(time), network_(network), agenda_(agenda) { }

Process::~Process() = default;

void Process::activate(double time, bool relative) {
	if (relative) {
		time_ += time;
	}
	else {
		time_ = time;
	}
	agenda_->push(this);
}

double Process::get_time() const {
	return time_;
}

bool Process::isTerminated() const {
	return terminated_;
}

void Process::setTerminated() {
	terminated_ = true;

	// means all users from the buffer and waiting buffer served
	if(agenda_->empty()) {
		endSimulation = true;
	}
}


bool Process::getEndSimulationCondition() const {
	return endSimulation;
}

