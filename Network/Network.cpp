//
// Created by Pawel Biniak on 23/03/2023.
//

#include "Network.h"

Network::Network() = default;

Network::~Network() = default;

// adding user to a buffer (to network system)
void Network::addUserToNetwork(User *u) {
		if(get_buffer_size() < Constants::n) {
			buffer_.push(u);
		}
		else {
			waitingBuffer_.push(u);
			// dodatkowo powinniśmy zawieśić jego proces do momentu kiedy zwolni się miejsce w głównej kolejce
			u->sleep();
		}
}

void Network::removeUserFromNetwork(User *user) {
	numbersOfHandledUsers.push_back(user->get_id());
	if(numbersOfHandledUsers.size() == 300) {
		isUsersLimitReached = true;
	}

	std::queue<User*> tempBuffer;
	while (!buffer_.empty()) {
		User* currentUser = buffer_.front();
		buffer_.pop();

		if (currentUser->get_id() != user->get_id()) {
			tempBuffer.push(currentUser);
		}
	}

	buffer_ = std::move(tempBuffer);

	if(!waitingBuffer_.empty()) {
		User* firstWaitingUser = waitingBuffer_.front();
		buffer_.push(firstWaitingUser);
	}

}

size_t Network::get_buffer_size() {
	return buffer_.size();
}

size_t Network::get_waiting_buffer_size() {
	return waitingBuffer_.size();
}

bool Network::isWaitingBufforEmpty() {
	return waitingBuffer_.empty();
}

User *Network::getBufforLastElement() {
	return buffer_.back();
}

void Network::removeWaitingBufforFirstUser() {
	waitingBuffer_.pop();
}
