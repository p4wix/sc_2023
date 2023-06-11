//
// Created by Pawel Biniak on 13/04/2023.
//

#ifndef SC_2023_SIMULATOR_H
#define SC_2023_SIMULATOR_H

#include <iostream>

#include "../Network/Network.h"
#include "../Constants/Constants.h"
#include "../User/User.h"

class Simulator {
	double clock_{};
	Network* network_ = nullptr;

public:
	UniformGenerator* speedGenerator; // uniform distribution scaled [5;50]
	UniformGenerator* spawnTimeGenerator; // exponential distribution with intensity λ
	UniformGenerator* powerBaseStationGenerator; // Gaussian distribution with mean = 0 and standard deviation = 4
	char** argv_;

	explicit Simulator(Network*, char**);
	~Simulator();
	void run(int);
	void handleSeedFile();
};


#endif //SC_2023_SIMULATOR_H
