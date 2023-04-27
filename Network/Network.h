//
// Created by Pawel Biniak on 23/03/2023.
//

#ifndef SC_2023_NETWORK_H
#define SC_2023_NETWORK_H

#include <iostream>
#include <queue>
#include "../User/User.h"

class User;

class Network {
	std::queue<User*> buffer_;
	bool full_ = false; // true -> system full false user can join

public:
	static const size_t generate_user_max_time = 10;

	Network();
	~Network();

	void init();
	void addUserToNetwork(User* user);
	bool isNetworkFull();
	size_t get_buffer_size();
	User* getBufferFirst();
};

#endif //SC_2023_NETWORK_H
