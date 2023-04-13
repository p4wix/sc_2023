//
// Created by Pawel Biniak on 23/03/2023.
//

#ifndef SC_2023_NETWORK_H
#define SC_2023_NETWORK_H

#include <queue>

class User;

class Network {
	std::queue<User*> buffer_;
	bool full_ = false; // true -> system full false user can join

public:
	Network();
	~Network();

	void init();
	void generateUser(User* user);
	size_t get_buffer_size();
};

#endif //SC_2023_NETWORK_H
