//
// Created by Pawel Biniak on 13/04/2023.
//

#include "Process.h"

Process::Process(size_t time, Network* network, Agenda* agenda) : time_(time), network_(network), agenda_(agenda) { }

Process::~Process() = default;

std::size_t Process::get_time() { return time_; }

