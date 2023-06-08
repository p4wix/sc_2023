#include "Simulator/Simulator.h"

int main() {
	auto* network = new Network();
	auto simulator = Simulator(network);
	simulator.run(1000000);
	// 1h = 3600000

//	UniformGenerator speedGenerator(144311); // rozkład równomierny przeskalowany o [5;50]
//	UniformGenerator spawnTimeGenerator(197555725); // rozkład wykładniczym o intensywności λ
//	UniformGenerator powerBaseStationGenerator(756247811);; // rozkład Gaussa z średnią 0 i odchyleniem 4
//
//	for (int i = 0; i < 20; ++i) {
//		std::cout << spawnTimeGenerator.RandExp(Constants::lambda)<< std::endl;
//	}

	return 0;
}