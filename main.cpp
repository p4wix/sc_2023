#include "Simulator/Simulator.h"

int main(int argc, char *argv[]) {
	auto* network = new Network(argv);
	auto simulator = Simulator(network, argv);
	simulator.run(10000); // sekundy

//	UniformGenerator g(1226428730);
//	for (int i =0 ; i < 100; ++i) {
//		std::cout << g.RandExp(0.04255) << std::endl;
//	}


	return 0;
}