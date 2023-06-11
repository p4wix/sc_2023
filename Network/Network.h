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

public:
	char** argv_;

	int waitingBuffer_{};
	int allUsers{};
	bool isUsersLimitReached{};
	int numbersOfHandledUsers{};
	std::fstream currentUsersNumberInBuffersFile;
	std::fstream currentUsersDisconnectReportFile;
	std::fstream currentUsersChangeStationReportFile;

	Network(char**);
	~Network();

	void addUserToNetwork(User*);
	void removeUserFromNetwork(User*);
	void handleFiles();
	void decrementWaitingBuffer();

	void sendCurrentUsersNumberInBuffersReport(double, int);
	void sendCurrentUserDisconnectReport(User*);
	void sendCurrentUserChangeStationReport(User*);

	size_t get_buffer_size();
};

#endif //SC_2023_NETWORK_H
