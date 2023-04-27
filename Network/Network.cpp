//
// Created by Pawel Biniak on 23/03/2023.
//

#include "Network.h"

Network::Network() {};

Network::~Network() {};

// make sure that queue are empty before we start adding users.
void Network::init() {
	while (!buffer_.empty())
	{
		delete buffer_.front();
		buffer_.pop();
	}
	full_ = false;
}

// adding user to a buffer (to network system)
void Network::addUserToNetwork(User *u) {
	buffer_.push(u);
	std::cout << "Generated User id:" << u->getId() << "\n";
}

User* Network::getBufferFirst() {
	return buffer_.front();
}

// get size of the current active users in network system
size_t Network::get_buffer_size() {
	return buffer_.size();
}

bool Network::isNetworkFull() {
	if(buffer_.size() == 20) {
		full_ = true;
	}
	else {
		full_ = false;
	}
	return full_;
}

