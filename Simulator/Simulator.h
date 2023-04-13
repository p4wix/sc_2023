//
// Created by Pawel Biniak on 13/04/2023.
//

#ifndef SC_2023_SIMULATOR_H
#define SC_2023_SIMULATOR_H

#include "../Network/Network.h"

class Simulator {
	size_t clock_ = 0;
	Network* network_ = nullptr;

public:
	explicit Simulator(Network*);
	void run(int);
};


#endif //SC_2023_SIMULATOR_H
