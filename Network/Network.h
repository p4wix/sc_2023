//
// Created by Pawel Biniak on 23/03/2023.
//

#ifndef SC_2023_NETWORK_H
#define SC_2023_NETWORK_H

#include <iostream>
#include <queue>
#include <list>
#include "../User/User.h"

class User;

class Network {
	std::queue<User*> buffer_;
	std::queue<User*> waitingBuffer_;

public:
	bool isUsersLimitReached{};
	std::list<int> numbersOfHandledUsers{};

	Network();
	~Network();

	void addUserToNetwork(User*);
	void removeUserFromNetwork(User*);
	bool isWaitingBufforEmpty();

	size_t get_buffer_size();
	size_t get_waiting_buffer_size();

	User* getBufforLastElement();
	void removeWaitingBufforFirstUser();
};

#endif //SC_2023_NETWORK_H
