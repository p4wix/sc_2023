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
	std::fstream resultsFile;

public:
	UniformGenerator speedGenerator; // rozkład równomierny przeskalowany o [5;50]
	UniformGenerator spawnTimeGenerator; // rozkład wykładniczym o intensywności λ
	UniformGenerator powerBaseStationGenerator; // rozkład Gaussa z średnią 0 i odchyleniem 4

	explicit Simulator(Network*);
	~Simulator();
	void run(int);
	void handleResultsFile();
	void handleCollectNetworkDataToFile();
};


#endif //SC_2023_SIMULATOR_H
