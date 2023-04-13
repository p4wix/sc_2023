#include "Simulator/Simulator.h"

int main() {
	auto* network = new Network();
	auto simulator = Simulator(network);

	simulator.run(10);
	return 0;
}
