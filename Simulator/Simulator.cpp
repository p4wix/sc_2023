//
// Created by Pawel Biniak on 13/04/2023.
//

#include "Simulator.h"

Simulator::Simulator(Network* network) : network_(network) { }

void Simulator::run(int) {
	clock_ = 0;
	network_->init();
	std::cout << "Started Simulation method process interaction (M4): \n";

	auto cmp = [](Process* left, Process* right) { return left->get_time() > right->get_time(); };
	Process::Agenda agenda(cmp);

	// Create first user process
	size_t id = 0;
	auto user = new User(clock_, network_, &agenda, id, Constants::v(), Constants::l);
	//user->activate(0); // activate now
}
