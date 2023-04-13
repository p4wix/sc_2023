#include "Simulator/Simulator.h"

int main() {
	Network* network = new Network();
	Simulator simulator = Simulator(network);

	simulator.run(10);
	return 0;
}
