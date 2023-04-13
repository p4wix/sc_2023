//
// Created by Pawel Biniak on 13/04/2023.
//

#include "Simulator.h"

Simulator::Simulator(Network* network) : network_(network) { }

void Simulator::run(int) {
	clock_ = 0;
	network_->init();
}
