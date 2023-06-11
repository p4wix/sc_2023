//
// Created by Pawel Biniak on 13/04/2023.
//

#include "Simulator.h"

Simulator::Simulator(Network* network, char** argv) : network_(network), argv_(argv)
{
	handleSeedFile();
}

Simulator::~Simulator() {
	delete network_;
}

void Simulator::run(int time) {
	std::cout << "Started Simulation method process interaction (M4): \n";

	clock_ = 0;

	// function that compares the activation times of two processes and returns true if the activation time of the process on the right is less
	auto cmp = [](Process *left, Process *right) { return left->get_time() > right->get_time(); };
	Process::Agenda agenda(cmp);

	// setting up first user process
	int id = 0;
	auto user = new User(clock_, network_, &agenda, id, speedGenerator->RandScaled(), Constants::x, speedGenerator,
											 spawnTimeGenerator, powerBaseStationGenerator, argv_);
	user->activate(0);

	// main loop
	while (clock_ < time) {
		// we take process from top, that have smallest activation time, so it will be next executed
		Process *process = agenda.top();

		// when all users served
		if(network_->isUsersLimitReached){
			std::cout << "\n\n" << network_->numbersOfHandledUsers << " users buffer served\nEND of the Simulation\n\n";
			break;
		}

		// remove it from queue
		agenda.pop();

		// Setting the simulation time to the current process activation time
		clock_ = process->get_time();

		std::cout << "Simulation Time:" << clock_ << std::endl;

		// save current report data to result
		//network_->sendCurrentUsersNumberInBuffersReport(clock_, process->userId());

		// execute current process first from agenda, that has the less activation time. (only those processes which are in the buffer)
		process->execute();

		// if it has been completed, release the memory
		if (process->isTerminated()) {
			delete process;
		}
	}
}

void Simulator::handleSeedFile() {
	// std::stoi(argv_[1])
	int seedPackNumber = std::stoi(argv_[1]);
	std::cout << seedPackNumber << std::endl;
	std::string file_name = "../Generator/Seed/seed-" + std::to_string(seedPackNumber) + ".txt";
	std::cout << file_name << std::endl;
	std::ifstream seedFile(file_name, std::ios::in);

	if (seedFile.is_open()) {
		int speedSeed, spawnTimeSeed, powerBaseStationSeed;
		seedFile >> speedSeed >> spawnTimeSeed >> powerBaseStationSeed;
		std::cout << speedSeed <<" " << spawnTimeSeed <<" "<< powerBaseStationSeed << std::endl;

		speedGenerator = new UniformGenerator(speedSeed);
		spawnTimeGenerator = new UniformGenerator(spawnTimeSeed);
		powerBaseStationGenerator = new UniformGenerator(powerBaseStationSeed);

		seedFile.close();
	}
	else {
		std::cout << "Seed file open error" << std::endl;
	}
}


