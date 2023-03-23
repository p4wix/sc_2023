//
// Created by Pawel Biniak on 23/03/2023.
//

#include "Network.h"

void Network::spawnUser() {
	User* u = new User(Constants::x, Constants::v());
	users.push_back(u);
}
