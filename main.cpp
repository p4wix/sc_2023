#include "Simulator/Simulator.h"

int main(int argc, char *argv[]) {
	auto* network = new Network(argv);
	auto simulator = Simulator(network, argv);
	simulator.run(10000);

	return 0;
}