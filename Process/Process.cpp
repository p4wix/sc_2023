//
// Created by Pawel Biniak on 13/04/2023.
//

#include "Process.h"

Process::Process(size_t time, Network* network, Agenda *agenda) : time_(time), network_(network), agenda_(agenda) {}

Process::~Process() { };

void Process::activate(size_t time, bool relative) {
	if (relative) {
		time_ += time;
	}
	else {
		time_ = time;
	}
	agenda_->push(this);
}

std::size_t Process::get_time() const { return time_; }

bool Process::isTerminated() const { return terminated_; }

void Process::setTerminated() { terminated_ = true; }




