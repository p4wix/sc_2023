//
// Created by Pawel Biniak on 23/03/2023.
//

#include "Network.h"

Network::Network() = default;

Network::~Network() = default;

void Network::init() {
	while (!buffer_.empty())
	{
		delete buffer_.front();
		buffer_.pop();
	}
	full_ = false;
}

void Network::generateUser(User *u) {
	buffer_.push(u);
	//std::cout << "Generated User id:" << u->getId() << "\n";
}

size_t Network::get_buffer_size() {
	return buffer_.size();
}
