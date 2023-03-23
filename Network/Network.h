//
// Created by Pawel Biniak on 23/03/2023.
//

#ifndef SC_2023_NETWORK_H
#define SC_2023_NETWORK_H

#include <vector>

#include "../User/User.h"
#include "../Constants/Constants.h"

class Network {
	std::vector<User*> users;

public:
	void spawnUser();
};


#endif //SC_2023_NETWORK_H
